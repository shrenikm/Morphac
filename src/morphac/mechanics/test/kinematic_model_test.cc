#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/include/kinematic_model.h"

namespace {

using Eigen::VectorXd;

using std::make_shared;
using std::shared_ptr;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::KinematicModel;

class SomeKinematicModel : public KinematicModel {
 public:
  SomeKinematicModel(const shared_ptr<State>& state,
                     const shared_ptr<ControlInput>& input)
      : KinematicModel(state, input) {}
  void ComputeDerivative() {
    // f(x, u) = x * u  - x
    VectorXd der(size_pose_ + size_velocity_);
    der << state_->get_pose_vector(), state_->get_velocity_vector();
    der = (der.array() * input_->get_input().array() - der.array()).matrix();

    derivative_->set_pose_vector(der.head(size_pose_));
    derivative_->set_velocity_vector(der.tail(size_velocity_));
  }
};

class KinematicModelTest : public ::testing::Test {
 protected:
  KinematicModelTest() {}

  void SetUp() override {}
};

TEST_F(KinematicModelTest, Subclass) {
  VectorXd pose_vector(3), velocity_vector(2), input_vector(5);
  pose_vector << 1, -2, 5;
  velocity_vector << -3, 2.5;
  input_vector << 1, 2, 3, 4, 7;

  shared_ptr<State> state = make_shared<State>(pose_vector, velocity_vector);
  shared_ptr<ControlInput> input = make_shared<ControlInput>(input_vector);
  SomeKinematicModel model(state, input);
  model.ComputeDerivative();
  const State& derivative = model.get_derivative();

  VectorXd expected_pose_derivative(3), expected_velocity_derivative(2);
  expected_pose_derivative << 0, -2, 10;
  expected_velocity_derivative << -9, 15;

  ASSERT_TRUE(expected_pose_derivative.isApprox(derivative.get_pose_vector()));
  ASSERT_TRUE(
      expected_velocity_derivative.isApprox(derivative.get_velocity_vector()));

  // Changing the values of the state
  state->set_pose_at(2, 3);
  state->set_velocity_at(1, 7);

  model.ComputeDerivative();

  // Updating expected values
  expected_pose_derivative(2) = 6;
  expected_velocity_derivative(1) = 42;

  // Checking if derivative has updated
  ASSERT_TRUE(
      expected_pose_derivative.isApprox(derivative.get_pose_vector()));
  ASSERT_TRUE(expected_velocity_derivative.isApprox(
      derivative.get_velocity_vector()));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
