#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/tricycle_model.h"

namespace {

using std::string;

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::TricycleModel;

class TricycleModelTest : public ::testing::Test {
 protected:
  TricycleModelTest() {}

  void SetUp() override {}
};

TEST_F(TricycleModelTest, Construction) {
  TricycleModel tricycle_model{"tricycle_model", 1.5, 2.3};

  ASSERT_EQ(tricycle_model.name, "tricycle_model");
  ASSERT_EQ(tricycle_model.size_pose, 4);
  ASSERT_EQ(tricycle_model.size_velocity, 0);
  ASSERT_EQ(tricycle_model.size_input, 2);
  ASSERT_EQ(tricycle_model.radius, 1.5);
  ASSERT_EQ(tricycle_model.length, 2.3);
}

TEST_F(TricycleModelTest, InvalidConstruction) {
  ASSERT_THROW(TricycleModel("invalid", -1, 1), std::invalid_argument);
  ASSERT_THROW(TricycleModel("invalid", 0, 1), std::invalid_argument);
  ASSERT_THROW(TricycleModel("invalid", 1, -1), std::invalid_argument);
  ASSERT_THROW(TricycleModel("invalid", 1, -1), std::invalid_argument);
}

TEST_F(TricycleModelTest, DerivativeComputation) {
  TricycleModel tricycle_model{"tricycle_model", 1.5, 2.5};
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
  ControlInput input1{input_vector1}, input2{input_vector2},
      input3{input_vector3}, input4{input_vector4}, input5{input_vector5};

  // Zero forward velocity does not make the robot move in x, y, or theta.
  desired_vector1 << 0, 0, 0, 1.;
  desired_vector2 << 0, 0, 1.2, 2;
  desired_vector3 << 3, 0, 0, 0;
  desired_vector4 << 0, 3, 0, -2;
  desired_vector5 << 0, 0, 6, 5;

  State derivative = tricycle_model.ComputeStateDerivative(state1, input1);
  ASSERT_TRUE(derivative.get_pose_vector().isApprox(desired_vector1));
  ASSERT_TRUE(derivative.IsVelocityEmpty());

  tricycle_model.ComputeStateDerivative(state1, input2, derivative);
  ASSERT_TRUE(derivative.get_pose_vector().isApprox(desired_vector2));
  ASSERT_TRUE(derivative.IsVelocityEmpty());

  tricycle_model.ComputeStateDerivative(state2, input3, derivative);
  ASSERT_TRUE(derivative.get_pose_vector().isApprox(desired_vector3));
  ASSERT_TRUE(derivative.IsVelocityEmpty());

  tricycle_model.ComputeStateDerivative(state3, input4, derivative);
  ASSERT_TRUE(derivative.get_pose_vector().isApprox(desired_vector4));
  ASSERT_TRUE(derivative.IsVelocityEmpty());

  tricycle_model.ComputeStateDerivative(state4, input5, derivative);
  ASSERT_TRUE(derivative.get_pose_vector().isApprox(desired_vector5));
  ASSERT_TRUE(derivative.IsVelocityEmpty());
}

TEST_F(TricycleModelTest, InvalidDerivativeComputation) {
  TricycleModel tricycle_model{"tricycle_model", 1, 1};
  State derivative1{3, 0};
  State derivative2{5, 0};

  // Computing the state derivative with incorrect state/input/derivative.
  ASSERT_THROW(
      tricycle_model.ComputeStateDerivative(State{3, 0}, ControlInput{2}),
      std::invalid_argument);
  ASSERT_THROW(
      tricycle_model.ComputeStateDerivative(State{5, 0}, ControlInput{2}),
      std::invalid_argument);
  ASSERT_THROW(
      tricycle_model.ComputeStateDerivative(State{3, 1}, ControlInput{2}),
      std::invalid_argument);
  ASSERT_THROW(
      tricycle_model.ComputeStateDerivative(State{3, 0}, ControlInput{1}),
      std::invalid_argument);
  ASSERT_THROW(
      tricycle_model.ComputeStateDerivative(State{3, 0}, ControlInput{3}),
      std::invalid_argument);
  ASSERT_THROW(tricycle_model.ComputeStateDerivative(
                   State{3, 0}, ControlInput{2}, derivative1),
               std::invalid_argument);
  ASSERT_THROW(tricycle_model.ComputeStateDerivative(
                   State{3, 0}, ControlInput{2}, derivative2),
               std::invalid_argument);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

