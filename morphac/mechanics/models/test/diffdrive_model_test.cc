#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/diffdrive_model.h"

namespace {

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::DiffDriveModel;

class DiffDriveModelTest : public ::testing::Test {
 protected:
  DiffDriveModelTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
};

TEST_F(DiffDriveModelTest, Construction) {
  DiffDriveModel diffdrive_model{1.5, 2.3};

  ASSERT_EQ(diffdrive_model.pose_size, 3);
  ASSERT_EQ(diffdrive_model.velocity_size, 0);
  ASSERT_EQ(diffdrive_model.control_input_size, 2);
  ASSERT_EQ(diffdrive_model.radius, 1.5);
  ASSERT_EQ(diffdrive_model.width, 2.3);
}

TEST_F(DiffDriveModelTest, InvalidConstruction) {
  ASSERT_THROW(DiffDriveModel(-1, 1), std::invalid_argument);
  ASSERT_THROW(DiffDriveModel(0, 1), std::invalid_argument);
  ASSERT_THROW(DiffDriveModel(1, -1), std::invalid_argument);
  ASSERT_THROW(DiffDriveModel(1, 0), std::invalid_argument);
}

TEST_F(DiffDriveModelTest, DerivativeComputation) {
  DiffDriveModel diffdrive_model{1.5, 2.5};
  VectorXd pose_vector1(3), pose_vector2(3);
  VectorXd control_input_vector1(2), control_input_vector2(2),
      control_input_vector3(2), control_input_vector4(2),
      control_input_vector5(2);
  VectorXd desired_vector1(3), desired_vector2(3), desired_vector3(3),
      desired_vector4(3), desired_vector5(3);
  pose_vector1 << 3, 4, M_PI / 2;
  pose_vector2 << -9, 10, 0;

  // Going straight.
  control_input_vector1 << 2, 2;
  // Turning left.
  control_input_vector2 << 1, 2;
  // Turning right.
  control_input_vector3 << 2, 1;
  // Turning in place (to the left).
  control_input_vector4 << -2, 2;
  // Turning in place (to the right).
  control_input_vector5 << 2, -2;

  desired_vector1 << 0, 3., 0;
  desired_vector2 << 2.25, 0, 0.6;
  desired_vector3 << 0, 2.25, -0.6;
  desired_vector4 << 0, 0, 2.4;
  desired_vector5 << 0, 0, -2.4;

  State state1{pose_vector1, VectorXd::Zero(0)};
  State state2{pose_vector2, VectorXd::Zero(0)};
  ControlInput control_input1{control_input_vector1},
      control_input2{control_input_vector2},
      control_input3{control_input_vector3},
      control_input4{control_input_vector4},
      control_input5{control_input_vector5};

  // Computing and verifying the derivative computation for different control
  // inputs.
  State derivative1 =
      diffdrive_model.ComputeStateDerivative(state1, control_input1);
  ASSERT_TRUE(derivative1.get_pose_data().isApprox(desired_vector1));
  ASSERT_TRUE(derivative1.IsVelocityEmpty());

  State derivative2 =
      diffdrive_model.ComputeStateDerivative(state2, control_input2);
  ASSERT_TRUE(derivative2.get_pose_data().isApprox(desired_vector2));
  ASSERT_TRUE(derivative2.IsVelocityEmpty());

  State derivative3 =
      diffdrive_model.ComputeStateDerivative(state1, control_input3);
  ASSERT_TRUE(derivative3.get_pose_data().isApprox(desired_vector3));
  ASSERT_TRUE(derivative3.IsVelocityEmpty());

  State derivative4 =
      diffdrive_model.ComputeStateDerivative(state2, control_input4);
  ASSERT_TRUE(derivative4.get_pose_data().isApprox(desired_vector4));
  ASSERT_TRUE(derivative4.IsVelocityEmpty());

  State derivative5 =
      diffdrive_model.ComputeStateDerivative(state1, control_input5);
  ASSERT_TRUE(derivative5.get_pose_data().isApprox(desired_vector5));
  ASSERT_TRUE(derivative5.IsVelocityEmpty());
}

TEST_F(DiffDriveModelTest, InvalidDerivativeComputation) {
  DiffDriveModel diffdrive_model{1, 1};

  // Computing the state derivative with incorrect state/control
  // input/derivative.
  ASSERT_THROW(
      diffdrive_model.ComputeStateDerivative(State(2, 0), ControlInput(2)),
      std::invalid_argument);
  ASSERT_THROW(
      diffdrive_model.ComputeStateDerivative(State(4, 0), ControlInput(2)),
      std::invalid_argument);
  ASSERT_THROW(
      diffdrive_model.ComputeStateDerivative(State(3, 1), ControlInput(2)),
      std::invalid_argument);
  ASSERT_THROW(
      diffdrive_model.ComputeStateDerivative(State(3, 0), ControlInput(1)),
      std::invalid_argument);
  ASSERT_THROW(
      diffdrive_model.ComputeStateDerivative(State(3, 0), ControlInput(3)),
      std::invalid_argument);
}

TEST_F(DiffDriveModelTest, StateNormalization) {
  DiffDriveModel diffdrive_model{1, 1};

  // Making sure that the angle gets normalized.
  State state1({0, 0, 2 * M_PI}, {});
  State state2({0, 0, 2 * M_PI + 4 * M_PI / 3.}, {});
  State state3({0, 0, -2 * M_PI - 4 * M_PI / 3.}, {});
  State normalized_state1({0, 0, 0}, {});
  State normalized_state2({0, 0, -2 * M_PI / 3.}, {});
  State normalized_state3({0, 0, 2 * M_PI / 3.}, {});

  ASSERT_TRUE(diffdrive_model.NormalizeState(state1) == normalized_state1);
  ASSERT_TRUE(diffdrive_model.NormalizeState(state2) == normalized_state2);
  ASSERT_TRUE(diffdrive_model.NormalizeState(state3) == normalized_state3);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

