#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/tricycle_model.h"

namespace {

using Eigen::VectorXd;

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::mechanics::models::TricycleModel;

class TricycleModelTest : public ::testing::Test {
 protected:
  TricycleModelTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
};

TEST_F(TricycleModelTest, Construction) {
  TricycleModel tricycle_model{1.5, 2.3};

  ASSERT_EQ(tricycle_model.size_pose, 4);
  ASSERT_EQ(tricycle_model.size_velocity, 0);
  ASSERT_EQ(tricycle_model.size_input, 2);
  ASSERT_EQ(tricycle_model.radius, 1.5);
  ASSERT_EQ(tricycle_model.length, 2.3);
}

TEST_F(TricycleModelTest, InvalidConstruction) {
  ASSERT_THROW(TricycleModel(-1, 1), std::invalid_argument);
  ASSERT_THROW(TricycleModel(0, 1), std::invalid_argument);
  ASSERT_THROW(TricycleModel(1, -1), std::invalid_argument);
  ASSERT_THROW(TricycleModel(1, -1), std::invalid_argument);
}

TEST_F(TricycleModelTest, DerivativeComputation) {
  TricycleModel tricycle_model{1.5, 2.5};
  VectorXd pose_vector1(4), pose_vector2(4), pose_vector3(4), pose_vector4(4);
  VectorXd input_vector1(2), input_vector2(2), input_vector3(2),
      input_vector4(2), input_vector5(2);
  VectorXd desired_vector1(4), desired_vector2(4), desired_vector3(4),
      desired_vector4(4), desired_vector5(4);

  pose_vector1 << 3, 4, M_PI / 2, M_PI / 2;
  pose_vector2 << -9, 10, 0, 0;
  pose_vector3 << 5, -13, M_PI / 2, 0;
  pose_vector4 << -2, -7, 0, M_PI / 2;

  // Forward velocity is zero.
  input_vector1 << 0, 1.;
  // Turning left.
  input_vector2 << 2, 2;
  // Not turning.
  input_vector3 << 2, 0;
  // Turning right.
  input_vector4 << 2, -2;
  input_vector5 << 10, 5;

  State state1{pose_vector1, VectorXd::Zero(0)};
  State state2{pose_vector2, VectorXd::Zero(0)};
  State state3{pose_vector3, VectorXd::Zero(0)};
  State state4{pose_vector4, VectorXd::Zero(0)};
  Input input1{input_vector1}, input2{input_vector2}, input3{input_vector3},
      input4{input_vector4}, input5{input_vector5};

  // Zero forward velocity does not make the robot move in x, y, or theta.
  desired_vector1 << 0, 0, 0, 1.;
  desired_vector2 << 0, 0, 1.2, 2;
  desired_vector3 << 3, 0, 0, 0;
  desired_vector4 << 0, 3, 0, -2;
  desired_vector5 << 0, 0, 6, 5;

  // Computing and verifying the derivative computation for different inputs.
  State derivative1 = tricycle_model.ComputeStateDerivative(state1, input1);
  ASSERT_TRUE(derivative1.get_pose_vector().isApprox(desired_vector1));
  ASSERT_TRUE(derivative1.IsVelocityEmpty());

  State derivative2 = tricycle_model.ComputeStateDerivative(state1, input2);
  ASSERT_TRUE(derivative2.get_pose_vector().isApprox(desired_vector2));
  ASSERT_TRUE(derivative2.IsVelocityEmpty());

  State derivative3 = tricycle_model.ComputeStateDerivative(state2, input3);
  ASSERT_TRUE(derivative3.get_pose_vector().isApprox(desired_vector3));
  ASSERT_TRUE(derivative3.IsVelocityEmpty());

  State derivative4 = tricycle_model.ComputeStateDerivative(state3, input4);
  ASSERT_TRUE(derivative4.get_pose_vector().isApprox(desired_vector4));
  ASSERT_TRUE(derivative4.IsVelocityEmpty());

  State derivative5 = tricycle_model.ComputeStateDerivative(state4, input5);
  ASSERT_TRUE(derivative5.get_pose_vector().isApprox(desired_vector5));
  ASSERT_TRUE(derivative5.IsVelocityEmpty());
}

TEST_F(TricycleModelTest, InvalidDerivativeComputation) {
  TricycleModel tricycle_model{1, 1};

  // Computing the state derivative with incorrect state/input/derivative.
  ASSERT_THROW(tricycle_model.ComputeStateDerivative(State(3, 0), Input(2)),
               std::invalid_argument);
  ASSERT_THROW(tricycle_model.ComputeStateDerivative(State(5, 0), Input(2)),
               std::invalid_argument);
  ASSERT_THROW(tricycle_model.ComputeStateDerivative(State(3, 1), Input(2)),
               std::invalid_argument);
  ASSERT_THROW(tricycle_model.ComputeStateDerivative(State(3, 0), Input(1)),
               std::invalid_argument);
  ASSERT_THROW(tricycle_model.ComputeStateDerivative(State(3, 0), Input(3)),
               std::invalid_argument);
}

TEST_F(TricycleModelTest, StateNormalization) {
  TricycleModel tricycle_model{1, 1};

  // Making sure that the angle get normalized.
  State state1({0, 0, 2 * M_PI, M_PI}, {});
  State state2({0, 0, 2 * M_PI + 4 * M_PI / 3., -2 * M_PI - 4 * M_PI / 3.}, {});
  State state3({0, 0, -2 * M_PI - 4 * M_PI / 3., 2 * M_PI + 4 * M_PI / 3.}, {});
  State normalized_state1({0, 0, 0, M_PI}, {});
  State normalized_state2({0, 0, -2 * M_PI / 3., 2 * M_PI / 3.}, {});
  State normalized_state3({0, 0, 2 * M_PI / 3., -2 * M_PI / 3.}, {});

  ASSERT_TRUE(tricycle_model.NormalizeState(state1) == normalized_state1);
  ASSERT_TRUE(tricycle_model.NormalizeState(state2) == normalized_state2);
  ASSERT_TRUE(tricycle_model.NormalizeState(state3) == normalized_state3);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

