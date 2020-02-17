#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/dubin_model.h"

namespace {

using std::string;

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::DubinModel;

class DubinModelTest : public ::testing::Test {
 protected:
  DubinModelTest() {}

  void SetUp() override {}
};

TEST_F(DubinModelTest, Sizes) {
  DubinModel dubin_model{"dubin_model", 1.5};

  ASSERT_EQ(dubin_model.name, "dubin_model");
  ASSERT_EQ(dubin_model.size_pose, 3);
  ASSERT_EQ(dubin_model.size_velocity, 0);
  ASSERT_EQ(dubin_model.size_input, 1);
  ASSERT_EQ(dubin_model.speed, 1.5);
}

TEST_F(DubinModelTest, DerivativeComputation) {
  DubinModel dubin_model{"dubin_model", 2.5};
  VectorXd pose_vector1(3), pose_vector2(3);
  VectorXd input_vector1(1), input_vector2(1);
  VectorXd desired_vector1(3), desired_vector2(3);
  pose_vector1 << 9, 10, M_PI / 2;
  pose_vector2 << 1.5, 2.3, 0.;
  input_vector1 << 5.5;
  input_vector2 << -1.5;
  desired_vector1 << 0., 2.5, 5.5;
  desired_vector2 << 2.5, 0., -1.5;

  State state1{pose_vector1, VectorXd::Zero(0)};
  ControlInput input1{input_vector1};
  State derivative1{3, 0};

  dubin_model.ComputeStateDerivative(state1, input1, derivative1);
  ASSERT_TRUE(derivative1.get_pose_vector().isApprox(desired_vector1));
  ASSERT_TRUE(derivative1.is_velocity_empty());

  State derivative2 = dubin_model.ComputeStateDerivative(
      State{pose_vector2, VectorXd::Zero(0)}, ControlInput{input_vector2});
  ASSERT_TRUE(derivative2.get_pose_vector().isApprox(desired_vector2));
  ASSERT_TRUE(derivative2.is_velocity_empty());
}

TEST_F(DubinModelTest, InvalidDerivativeComputation) {
  DubinModel dubin_model{"dubin_model", 1.0};
  State derivative1{2, 0};
  State derivative2{3, 1};

  // Computing the state derivative with incorrect state/input/derivative.
  ASSERT_THROW(dubin_model.ComputeStateDerivative(State{4, 0}, ControlInput{1}),
               std::invalid_argument);
  ASSERT_THROW(dubin_model.ComputeStateDerivative(State{3, 1}, ControlInput{1}),
               std::invalid_argument);
  ASSERT_THROW(dubin_model.ComputeStateDerivative(State{3, 0}, ControlInput{2}),
               std::invalid_argument);
  ASSERT_THROW(dubin_model.ComputeStateDerivative(State{3, 0}, ControlInput{1},
                                                  derivative1),
               std::invalid_argument);
  ASSERT_THROW(dubin_model.ComputeStateDerivative(State{3, 0}, ControlInput{1},
                                                  derivative2),
               std::invalid_argument);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
