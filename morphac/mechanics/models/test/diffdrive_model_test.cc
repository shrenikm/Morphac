#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/diffdrive_model.h"

namespace {

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::mechanics::models::DiffDriveModel;

class DiffDriveModelTest : public ::testing::Test {
 protected:
  DiffDriveModelTest() {}

  void SetUp() override {}
};

TEST_F(DiffDriveModelTest, Construction) {
  DiffDriveModel diffdrive_model{1.5, 2.3};

  ASSERT_EQ(diffdrive_model.size_pose, 3);
  ASSERT_EQ(diffdrive_model.size_velocity, 0);
  ASSERT_EQ(diffdrive_model.size_input, 2);
  ASSERT_EQ(diffdrive_model.radius, 1.5);
  ASSERT_EQ(diffdrive_model.length, 2.3);
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
  VectorXd input_vector1(2), input_vector2(2), input_vector3(2),
      input_vector4(2), input_vector5(2);
  VectorXd desired_vector1(3), desired_vector2(3), desired_vector3(3),
      desired_vector4(3), desired_vector5(3);
  pose_vector1 << 3, 4, M_PI / 2;
  pose_vector2 << -9, 10, 0;

  // Going straight.
  input_vector1 << 2, 2;
  // Turning left.
  input_vector2 << 1, 2;
  // Turning right.
  input_vector3 << 2, 1;
  // Turning in place (to the left).
  input_vector4 << -2, 2;
  // Turning in place (to the right).
  input_vector5 << 2, -2;

  desired_vector1 << 0, 3., 0;
  desired_vector2 << 2.25, 0, 0.6;
  desired_vector3 << 0, 2.25, -0.6;
  desired_vector4 << 0, 0, 2.4;
  desired_vector5 << 0, 0, -2.4;

  State state1{pose_vector1, VectorXd::Zero(0)};
  State state2{pose_vector2, VectorXd::Zero(0)};
  Input input1{input_vector1}, input2{input_vector2}, input3{input_vector3},
      input4{input_vector4}, input5{input_vector5};

  // Computing and verifying the derivative computation for different inputs.
  State derivative1 = diffdrive_model.ComputeStateDerivative(state1, input1);
  ASSERT_TRUE(derivative1.get_pose_vector().isApprox(desired_vector1));
  ASSERT_TRUE(derivative1.IsVelocityEmpty());

  State derivative2 = diffdrive_model.ComputeStateDerivative(state2, input2);
  ASSERT_TRUE(derivative2.get_pose_vector().isApprox(desired_vector2));
  ASSERT_TRUE(derivative2.IsVelocityEmpty());

  State derivative3 = diffdrive_model.ComputeStateDerivative(state1, input3);
  ASSERT_TRUE(derivative3.get_pose_vector().isApprox(desired_vector3));
  ASSERT_TRUE(derivative3.IsVelocityEmpty());

  State derivative4 = diffdrive_model.ComputeStateDerivative(state2, input4);
  ASSERT_TRUE(derivative4.get_pose_vector().isApprox(desired_vector4));
  ASSERT_TRUE(derivative4.IsVelocityEmpty());

  State derivative5 = diffdrive_model.ComputeStateDerivative(state1, input5);
  ASSERT_TRUE(derivative5.get_pose_vector().isApprox(desired_vector5));
  ASSERT_TRUE(derivative5.IsVelocityEmpty());
}

TEST_F(DiffDriveModelTest, InvalidDerivativeComputation) {
  DiffDriveModel diffdrive_model{1, 1};

  // Computing the state derivative with incorrect state/input/derivative.
  ASSERT_THROW(diffdrive_model.ComputeStateDerivative(State(2, 0), Input(2)),
               std::invalid_argument);
  ASSERT_THROW(diffdrive_model.ComputeStateDerivative(State(4, 0), Input(2)),
               std::invalid_argument);
  ASSERT_THROW(diffdrive_model.ComputeStateDerivative(State(3, 1), Input(2)),
               std::invalid_argument);
  ASSERT_THROW(diffdrive_model.ComputeStateDerivative(State(3, 0), Input(1)),
               std::invalid_argument);
  ASSERT_THROW(diffdrive_model.ComputeStateDerivative(State(3, 0), Input(3)),
               std::invalid_argument);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

