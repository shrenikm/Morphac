#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/kinematic_model.h"

namespace {

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::KinematicModel;

class CustomKinematicModel : public KinematicModel {
 public:
  CustomKinematicModel(int pose_size, int velocity_size, int control_input_size,
                       double a)
      : KinematicModel(pose_size, velocity_size, control_input_size), a(a) {}

  State ComputeStateDerivative(
      const State& state, const ControlInput& control_input) const override {
    // f(x, u) = x * a * u - x
    VectorXd derivative_vector(state.get_size());
    derivative_vector << state.get_data();
    derivative_vector =
        (derivative_vector.array() * a * control_input.get_data().array() -
         derivative_vector.array())
            .matrix();

    State derivative = State::CreateLike(state);
    derivative.set_pose_data(derivative_vector.head(pose_size));
    derivative.set_velocity_data(derivative_vector.tail(velocity_size));

    return derivative;
  }

  double a;
};

class KinematicModelTest : public ::testing::Test {
 protected:
  KinematicModelTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
};

TEST_F(KinematicModelTest, Sizes) {
  CustomKinematicModel model1{2, 2, 3, 1};
  CustomKinematicModel model2{20, 25, 13, 2.5};

  ASSERT_EQ(model1.pose_size, 2);
  ASSERT_EQ(model2.pose_size, 20);

  ASSERT_EQ(model1.velocity_size, 2);
  ASSERT_EQ(model2.velocity_size, 25);

  ASSERT_EQ(model1.control_input_size, 3);
  ASSERT_EQ(model2.control_input_size, 13);

  ASSERT_EQ(model1.a, 1);
  ASSERT_EQ(model2.a, 2.5);
}

TEST_F(KinematicModelTest, DerivativeComputation) {
  VectorXd pose_vector(3), velocity_vector(2), control_input_vector(5);
  pose_vector << 1, -2, 5;
  velocity_vector << -3, 2.5;
  control_input_vector << 1, 2, 3, 4, 7;

  State state(pose_vector, velocity_vector);
  ControlInput control_input(control_input_vector);

  CustomKinematicModel model{3, 2, 5, 1.0};

  VectorXd expected_pose_derivative(3), expected_velocity_derivative(2);
  expected_pose_derivative << 0, -2, 10;
  expected_velocity_derivative << -9, 15;

  // Changing the values of the state.
  state.get_pose()[2] = 3;
  state.get_velocity()[1] = 7;

  // Computing the derivative.
  State derivative = model.ComputeStateDerivative(state, control_input);

  // Updating expected values.
  expected_pose_derivative(2) = 6;
  expected_velocity_derivative(1) = 42;

  // Checking if derivative has updated.
  ASSERT_TRUE(expected_pose_derivative.isApprox(derivative.get_pose_data()));
  ASSERT_TRUE(
      expected_velocity_derivative.isApprox(derivative.get_velocity_data()));
}

TEST_F(KinematicModelTest, StateNormalization) {
  // Making sure that the NormalizeState interface works.
  // As we don't override NormalizeState in SomeKinematicModel, calling this
  // function should return the same state.
  CustomKinematicModel model{4, 2, 2, 0};
  State state({1, 2, 3, 4}, {5, 6});

  ASSERT_TRUE(model.NormalizeState(state) == state);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
