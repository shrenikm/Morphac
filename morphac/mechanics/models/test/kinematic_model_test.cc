#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/kinematic_model.h"

namespace {

using std::string;

using Eigen::VectorXd;

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::mechanics::models::KinematicModel;

class SomeKinematicModel : public KinematicModel {
 public:
  SomeKinematicModel(string name, int size_pose, int size_velocity,
                     int size_input, double a)
      : KinematicModel(name, size_pose, size_velocity, size_input), a(a) {}

  State ComputeStateDerivative(const State& state, const Input& input) const {
    // f(x, u) = x * a * u - x
    VectorXd derivative_vector(state.get_size());
    derivative_vector << state.get_state_vector();
    derivative_vector =
        (derivative_vector.array() * a * input.get_input_vector().array() -
         derivative_vector.array())
            .matrix();

    State derivative = State::CreateLike(state);
    derivative.set_pose_vector(derivative_vector.head(size_pose));
    derivative.set_velocity_vector(derivative_vector.tail(size_velocity));

    return derivative;
  }

  double a;
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
  Input input(input_vector);

  SomeKinematicModel model{"model", 3, 2, 5, 1.0};

  VectorXd expected_pose_derivative(3), expected_velocity_derivative(2);
  expected_pose_derivative << 0, -2, 10;
  expected_velocity_derivative << -9, 15;

  // Changing the values of the state.
  state.get_pose()(2) = 3;
  state.get_velocity()(1) = 7;

  // Computing the derivative.
  State derivative = model.ComputeStateDerivative(state, input);

  // Updating expected values.
  expected_pose_derivative(2) = 6;
  expected_velocity_derivative(1) = 42;

  // Checking if derivative has updated.
  ASSERT_TRUE(expected_pose_derivative.isApprox(derivative.get_pose_vector()));
  ASSERT_TRUE(
      expected_velocity_derivative.isApprox(derivative.get_velocity_vector()));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
