#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/ackermann_model.h"

namespace {

using std::vector;

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::AckermannModel;

class AckermannModelTest : public ::testing::Test {
 protected:
  AckermannModelTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
};

TEST_F(AckermannModelTest, Construction) {
  AckermannModel ackermann_model{1.5, 2.3};

  ASSERT_EQ(ackermann_model.pose_size, 4);
  ASSERT_EQ(ackermann_model.velocity_size, 0);
  ASSERT_EQ(ackermann_model.control_input_size, 2);
  ASSERT_EQ(ackermann_model.width, 1.5);
  ASSERT_EQ(ackermann_model.length, 2.3);
}

TEST_F(AckermannModelTest, InvalidConstruction) {
  ASSERT_THROW(AckermannModel(-1, 1), std::invalid_argument);
  ASSERT_THROW(AckermannModel(0, 1), std::invalid_argument);
  ASSERT_THROW(AckermannModel(1, -1), std::invalid_argument);
  ASSERT_THROW(AckermannModel(1, -1), std::invalid_argument);
}

TEST_F(AckermannModelTest, DerivativeComputation) {
  AckermannModel ackermann_model{1., 2.};
  VectorXd pose_vector1(4), pose_vector2(4), pose_vector3(4), pose_vector4(4);
  VectorXd control_input_vector1(2), control_input_vector2(2),
      control_input_vector3(2), control_input_vector4(2);
  VectorXd desired_vector1(4), desired_vector2(4), desired_vector3(4),
      desired_vector4(4);

  pose_vector1 << 0, 0, M_PI / 2, 0.;
  pose_vector2 << -5, 10, 0, 0;
  pose_vector3 << 10, -5, M_PI / 2, 0;
  pose_vector4 << -7, -2, 0, M_PI / 4;

  State state1{pose_vector1, VectorXd::Zero(0)};
  State state2{pose_vector2, VectorXd::Zero(0)};
  State state3{pose_vector3, VectorXd::Zero(0)};
  State state4{pose_vector4, VectorXd::Zero(0)};

  // Forward velocity is zero.
  control_input_vector1 << 0, 1.;
  // Turning left.
  control_input_vector2 << 1, 5;
  // Not turning.
  control_input_vector3 << 2, 0;
  // Turning right.
  control_input_vector4 << 5, -1;

  ControlInput control_input1{control_input_vector1},
      control_input2{control_input_vector2},
      control_input3{control_input_vector3},
      control_input4{control_input_vector4};

  // Zero forward velocity does not make the robot move in x, y, or theta.
  desired_vector1 << 0, 0, 0, 1.;
  desired_vector2 << 1, 0, 0, 5;
  desired_vector3 << 0, 2, 0, 0;
  desired_vector4 << 5, 0, 2.5, -1;

  // Computing and verifying the derivative computation for different control
  // inputs.
  State derivative1 =
      ackermann_model.ComputeStateDerivative(state1, control_input1);
  ASSERT_TRUE(derivative1.get_pose_data().isApprox(desired_vector1));
  ASSERT_TRUE(derivative1.IsVelocityEmpty());

  State derivative2 =
      ackermann_model.ComputeStateDerivative(state2, control_input2);
  ASSERT_TRUE(derivative2.get_pose_data().isApprox(desired_vector2));
  ASSERT_TRUE(derivative2.IsVelocityEmpty());

  State derivative3 =
      ackermann_model.ComputeStateDerivative(state3, control_input3);
  ASSERT_TRUE(derivative3.get_pose_data().isApprox(desired_vector3));
  ASSERT_TRUE(derivative3.IsVelocityEmpty());

  State derivative4 =
      ackermann_model.ComputeStateDerivative(state4, control_input4);
  ASSERT_TRUE(derivative4.get_pose_data().isApprox(desired_vector4));
  ASSERT_TRUE(derivative4.IsVelocityEmpty());
}

TEST_F(AckermannModelTest, InvalidDerivativeComputation) {
  AckermannModel ackermann_model{1., 1.};

  // Compute the state derivative with incorrect state/control.
  ASSERT_THROW(
      ackermann_model.ComputeStateDerivative(State(3, 0), ControlInput(2)),
      std::invalid_argument);
  ASSERT_THROW(
      ackermann_model.ComputeStateDerivative(State(5, 0), ControlInput(2)),
      std::invalid_argument);
  ASSERT_THROW(
      ackermann_model.ComputeStateDerivative(State(3, 1), ControlInput(2)),
      std::invalid_argument);
  ASSERT_THROW(
      ackermann_model.ComputeStateDerivative(State(3, 0), ControlInput(1)),
      std::invalid_argument);
  ASSERT_THROW(
      ackermann_model.ComputeStateDerivative(State(3, 0), ControlInput(3)),
      std::invalid_argument);

  // It should also throw an error if the steering angle is invalid.
  ASSERT_THROW(ackermann_model.ComputeStateDerivative(
                   State({0., 0., 0., 2 * M_PI / 3}, {}), ControlInput(2)),
               std::invalid_argument);
  ASSERT_THROW(ackermann_model.ComputeStateDerivative(
                   State({0., 0., M_PI, -2 * M_PI / 3}, {}), ControlInput(2)),
               std::invalid_argument);
}

TEST_F(AckermannModelTest, ComputeSteeringAngles) {
  AckermannModel ackermann_model{1., 2.};

  // Sanity check for when the ideal steering is zero. In this case the inner
  // and outer angles must also be zero.
  double ideal_steering_angle = 0.;
  double inner_steering =
      ackermann_model.ComputeInnerSteeringAngle(ideal_steering_angle);
  double outer_steering =
      ackermann_model.ComputeOuterSteeringAngle(ideal_steering_angle);
  ASSERT_EQ(inner_steering, 0.);
  ASSERT_EQ(outer_steering, 0.);

  // Steering angles for an ideal steering angle of 45 degrees (Turning to the
  // left).
  ideal_steering_angle = M_PI / 4;
  inner_steering =
      ackermann_model.ComputeInnerSteeringAngle(ideal_steering_angle);
  outer_steering =
      ackermann_model.ComputeOuterSteeringAngle(ideal_steering_angle);

  // The angles must follow inner > ideal > outer.
  ASSERT_GT(inner_steering, ideal_steering_angle);
  ASSERT_GT(ideal_steering_angle, outer_steering);

  // The same thing applies for when the ideal steering is to the right.
  // Testing if the function that returns both the inner and outer angles works.

  ideal_steering_angle = -M_PI / 4;
  vector<double> steering_angles =
      ackermann_model.ComputeSteeringAngles(ideal_steering_angle);

  ASSERT_GT(steering_angles[0], ideal_steering_angle);
  ASSERT_GT(ideal_steering_angle, steering_angles[1]);
}

TEST_F(AckermannModelTest, StateNormalization) {
  AckermannModel ackermann_model{1, 1};

  // Making sure that the angle gets normalized.
  State state1({0, 0, 2 * M_PI, M_PI}, {});
  State state2({0, 0, 2 * M_PI + 4 * M_PI / 3., -2 * M_PI - 4 * M_PI / 3.}, {});
  State state3({0, 0, -2 * M_PI - 4 * M_PI / 3., 2 * M_PI + 4 * M_PI / 3.}, {});
  State normalized_state1({0, 0, 0, M_PI}, {});
  State normalized_state2({0, 0, -2 * M_PI / 3., 2 * M_PI / 3.}, {});
  State normalized_state3({0, 0, 2 * M_PI / 3., -2 * M_PI / 3.}, {});

  ASSERT_TRUE(ackermann_model.NormalizeState(state1) == normalized_state1);
  ASSERT_TRUE(ackermann_model.NormalizeState(state2) == normalized_state2);
  ASSERT_TRUE(ackermann_model.NormalizeState(state3) == normalized_state3);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

