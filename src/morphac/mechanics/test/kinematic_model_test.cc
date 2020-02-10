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
  SomeKinematicModel(int size_pose, int size_velocity, int size_input)
      : KinematicModel(size_pose, size_velocity, size_input) {}

  void ComputeStateDerivative(const State& state, const ControlInput& input,
                              State& derivative) {
    VectorXd derivative_vector(state.get_size());
    derivative_vector << state.get_state_vector();
    derivative_vector =
        (derivative_vector.array() * input.get_input_vector().array() -
         derivative_vector.array())
            .matrix();
    derivative.set_pose_vector(derivative_vector.head(size_pose_));
    derivative.set_velocity_vector(derivative_vector.tail(size_velocity_));
  }
  State ComputeStateDerivative(const State& state, const ControlInput& input) {
    State derivative(size_pose_, size_velocity_);
    ComputeStateDerivative(state, input, derivative);
    return derivative;
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

  State state(pose_vector, velocity_vector);
  ControlInput input(input_vector);

  SomeKinematicModel model(3, 2, 5);

  VectorXd expected_pose_derivative(3), expected_velocity_derivative(2);
  expected_pose_derivative << 0, -2, 10;
  expected_velocity_derivative << -9, 15;

  State derivative1(3, 2);

  // Computing the derivative using the function overload that takes the
  // reference
  model.ComputeStateDerivative(state, input, derivative1);

  // Checking if the computed derivative is accurate
  ASSERT_TRUE(expected_pose_derivative.isApprox(derivative1.get_pose_vector()));
  ASSERT_TRUE(
      expected_velocity_derivative.isApprox(derivative1.get_velocity_vector()));

  // Changing the values of the state
  state.set_pose_at(2, 3);
  state.set_velocity_at(1, 7);

  // Now we use the other overload to compute the derivative.
  State derivative2 = model.ComputeStateDerivative(state, input);

  // Updating expected values
  expected_pose_derivative(2) = 6;
  expected_velocity_derivative(1) = 42;

  // Checking if derivative has updated
  ASSERT_TRUE(expected_pose_derivative.isApprox(derivative2.get_pose_vector()));
  ASSERT_TRUE(
      expected_velocity_derivative.isApprox(derivative2.get_velocity_vector()));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
