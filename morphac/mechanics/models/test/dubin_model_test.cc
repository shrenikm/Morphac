#include "mechanics/models/include/dubin_model.h"

#include "Eigen/Dense"
#include "gtest/gtest.h"

namespace {

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::DubinModel;
using morphac::robot::blueprint::Footprint;

class DubinModelTest : public ::testing::Test {
 protected:
  DubinModelTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override{};
};

TEST_F(DubinModelTest, Construction) {
  DubinModel dubin_model{1.5};

  ASSERT_EQ(dubin_model.pose_size, 3);
  ASSERT_EQ(dubin_model.velocity_size, 0);
  ASSERT_EQ(dubin_model.control_input_size, 1);
  ASSERT_EQ(dubin_model.speed, 1.5);
}

TEST_F(DubinModelTest, DerivativeComputation) {
  DubinModel dubin_model{2.5};
  VectorXd pose_vector1(3), pose_vector2(3);
  VectorXd control_input_vector1(1), control_input_vector2(1);
  VectorXd desired_vector1(3), desired_vector2(3);
  pose_vector1 << 9, 10, M_PI / 2;
  pose_vector2 << 1.5, 2.3, 0.;
  control_input_vector1 << 5.5;
  control_input_vector2 << -1.5;
  desired_vector1 << 0., 2.5, 5.5;
  desired_vector2 << 2.5, 0., -1.5;

  State state1{pose_vector1, VectorXd::Zero(0)};
  ControlInput control_input1{control_input_vector1};

  // Computing and verifying the derivative computation for different control
  // inputs.
  State derivative1 =
      dubin_model.ComputeStateDerivative(state1, control_input1);
  ASSERT_TRUE(derivative1.get_pose_data().isApprox(desired_vector1));
  ASSERT_TRUE(derivative1.IsVelocityEmpty());

  State derivative2 =
      dubin_model.ComputeStateDerivative(State{pose_vector2, VectorXd::Zero(0)},
                                         ControlInput{control_input_vector2});
  ASSERT_TRUE(derivative2.get_pose_data().isApprox(desired_vector2));
  ASSERT_TRUE(derivative2.IsVelocityEmpty());
}

TEST_F(DubinModelTest, InvalidDerivativeComputation) {
  DubinModel dubin_model{1.0};

  // Computing the state derivative with incorrect state/control
  // input/derivative.
  ASSERT_THROW(dubin_model.ComputeStateDerivative(State(2, 0), ControlInput(1)),
               std::invalid_argument);
  ASSERT_THROW(dubin_model.ComputeStateDerivative(State(4, 0), ControlInput(1)),
               std::invalid_argument);
  ASSERT_THROW(dubin_model.ComputeStateDerivative(State(3, 1), ControlInput(1)),
               std::invalid_argument);
  ASSERT_THROW(dubin_model.ComputeStateDerivative(State(3, 0), ControlInput(0)),
               std::invalid_argument);
  ASSERT_THROW(dubin_model.ComputeStateDerivative(State(3, 0), ControlInput(2)),
               std::invalid_argument);
}

TEST_F(DubinModelTest, StateNormalization) {
  DubinModel dubin_model{1};

  // Making sure that the angle gets normalized.
  State state1({0, 0, 2 * M_PI}, {});
  State state2({0, 0, 2 * M_PI + 4 * M_PI / 3.}, {});
  State state3({0, 0, -2 * M_PI - 4 * M_PI / 3.}, {});
  State normalized_state1({0, 0, 0}, {});
  State normalized_state2({0, 0, -2 * M_PI / 3.}, {});
  State normalized_state3({0, 0, 2 * M_PI / 3.}, {});

  ASSERT_TRUE(dubin_model.NormalizeState(state1) == normalized_state1);
  ASSERT_TRUE(dubin_model.NormalizeState(state2) == normalized_state2);
  ASSERT_TRUE(dubin_model.NormalizeState(state3) == normalized_state3);
}

TEST_F(DubinModelTest, DefaultFootprint) {
  DubinModel dubin_model{1};

  Footprint footprint = dubin_model.DefaultFootprint();

  // Just make sure that the footprint is a triangle.
  ASSERT_EQ(footprint.get_data().rows(), 3.);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
