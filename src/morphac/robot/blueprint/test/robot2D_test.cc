#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "robot/blueprint/include/robot2D.h"

namespace {

using Eigen::VectorXd;
using Eigen::MatrixXd;

using std::make_shared;
using std::shared_ptr;

using morphac::constructs::ControlInput;
using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;
using morphac::mechanics::KinematicModel;
using morphac::robot::blueprint::Robot2D;

class SomeKinematicModel : public KinematicModel {
 public:
  SomeKinematicModel(const shared_ptr<State>& state,
                     const shared_ptr<ControlInput>& input)
      : KinematicModel(state, input) {}
  void ComputeDerivative() {
    // f(x, u) = x * u  - x
    VectorXd der(size_pose_ + size_velocity_);
    der << state_->get_pose_vector(), state_->get_velocity_vector();
    der = (der.array() * input_->get_input_vector().array() - der.array())
              .matrix();

    derivative_->set_pose_vector(der.head(size_pose_));
    derivative_->set_velocity_vector(der.tail(size_velocity_));
  }
};

class Robot2DTest : public ::testing::Test {
 protected:
  Robot2DTest() {}

  void SetUp() override {
    pose_vector_ = VectorXd::Random(3);
    velocity_vector_ = VectorXd::Random(2);
    input_vector_ = VectorXd::Random(5);
    footprint_ = MatrixXd::Random(10, 2);
  }

  VectorXd pose_vector_, velocity_vector_, input_vector_;
  MatrixXd footprint_;
};

TEST_F(Robot2DTest, Creation) {
  shared_ptr<State> state = make_shared<State>(pose_vector_, velocity_vector_);
  shared_ptr<ControlInput> input = make_shared<ControlInput>(input_vector_);
  SomeKinematicModel model(state, input);
  Robot2D robot(model, footprint_);
}

TEST_F(Robot2DTest, Accessors) {
  shared_ptr<State> state = make_shared<State>(pose_vector_, velocity_vector_);
  shared_ptr<ControlInput> input = make_shared<ControlInput>(input_vector_);
  SomeKinematicModel model(state, input);
  Robot2D robot(model, footprint_);

  const KinematicModel& robot_kinematic_model = robot.get_kinematic_model();
  const State& robot_state = robot.get_state();
  const Pose& robot_pose = robot.get_pose();
  const Velocity& robot_velocity = robot.get_velocity();
  const MatrixXd robot_footprint = robot.get_footprint();

  ASSERT_EQ(robot_state.get_size(), 5);
  ASSERT_TRUE(
      robot_state.get_pose_vector().isApprox(robot_pose.get_pose_vector()));
  ASSERT_TRUE(robot_state.get_velocity_vector().isApprox(
      robot_velocity.get_velocity_vector()));
  ASSERT_TRUE(robot_pose.get_pose_vector().isApprox(pose_vector_));
  ASSERT_TRUE(robot_velocity.get_velocity_vector().isApprox(velocity_vector_));
  ASSERT_TRUE(robot_kinematic_model.get_input().get_input_vector().isApprox(
      input_vector_));

  // Updating the state and input values and checking if the references also
  // get updated
  VectorXd new_pose_vector = VectorXd::Random(3);
  VectorXd new_velocity_vector = VectorXd::Random(2);
  VectorXd new_input_vector = VectorXd::Random(5);

  state->set_pose_vector(new_pose_vector);
  state->set_velocity_vector(new_velocity_vector);
  input->set_input_vector(new_input_vector);

  ASSERT_EQ(robot_state.get_size(), 5);
  ASSERT_TRUE(
      robot_state.get_pose_vector().isApprox(robot_pose.get_pose_vector()));
  ASSERT_TRUE(robot_state.get_velocity_vector().isApprox(
      robot_velocity.get_velocity_vector()));
  ASSERT_TRUE(robot_pose.get_pose_vector().isApprox(new_pose_vector));
  ASSERT_TRUE(
      robot_velocity.get_velocity_vector().isApprox(new_velocity_vector));
  ASSERT_TRUE(robot_kinematic_model.get_input().get_input_vector().isApprox(
      new_input_vector));
}

TEST_F(Robot2DTest, InvalidFootprint) {
  // Invalid argument exception must be thrown for incorrect footprint
  shared_ptr<State> state = make_shared<State>(pose_vector_, velocity_vector_);
  shared_ptr<ControlInput> input = make_shared<ControlInput>(input_vector_);
  SomeKinematicModel model(state, input);
  ASSERT_THROW(Robot2D(model, MatrixXd::Random(0, 2)), std::invalid_argument);
  ASSERT_THROW(Robot2D(model, MatrixXd::Random(5, 0)), std::invalid_argument);
  ASSERT_THROW(Robot2D(model, MatrixXd::Random(5, 3)), std::invalid_argument);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

