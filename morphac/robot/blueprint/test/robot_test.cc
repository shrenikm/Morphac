#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "robot/blueprint/include/robot.h"

namespace {

using std::make_shared;
using std::shared_ptr;
using std::srand;

using Eigen::VectorXd;
using Eigen::MatrixXd;

using morphac::constructs::Input;
using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;
using morphac::mechanics::models::KinematicModel;
using morphac::robot::blueprint::Footprint;
using morphac::robot::blueprint::Robot;

class CustomKinematicModel : public KinematicModel {
 public:
  CustomKinematicModel(int pose_size, int velocity_size, int size_input)
      : KinematicModel(pose_size, velocity_size, size_input) {}

  State ComputeStateDerivative(const State& state, const Input& input) const {
    // f(x, u) = x * u  - x
    VectorXd derivative_vector(state.get_size());
    derivative_vector << state.get_data();
    derivative_vector =
        (derivative_vector.array() * input.get_data().array() -
         derivative_vector.array())
            .matrix();

    State derivative = State::CreateLike(state);
    derivative.set_pose_data(derivative_vector.head(pose_size));
    derivative.set_velocity_data(derivative_vector.tail(velocity_size));

    return derivative;
  }
};

class RobotTest : public ::testing::Test {
 protected:
  RobotTest() {
    // Set random seed for Eigen.
    srand(7);

    pose_vector_ = VectorXd::Random(3);
    velocity_vector_ = VectorXd::Random(2);
    input_vector_ = VectorXd::Random(5);
    footprint_matrix_ = MatrixXd::Random(10, 2);
  }

  void SetUp() override {}

  VectorXd pose_vector_, velocity_vector_, input_vector_;
  MatrixXd footprint_matrix_;
};

TEST_F(RobotTest, Construction) {
  CustomKinematicModel model(3, 2, 5);
  Footprint footprint(footprint_matrix_);
  Robot robot1{model, footprint};

  // Constructing with a temporary KinematicModel.
  Robot robot2{CustomKinematicModel{3, 2, 5}, footprint, State(3, 2)};
}

TEST_F(RobotTest, InvalidConstruction) {
  CustomKinematicModel model(3, 2, 5);
  Footprint footprint(footprint_matrix_);

  // Test invalid state/input dimensions.
  ASSERT_THROW(Robot(model, footprint, State(3, 3)), std::invalid_argument);
  ASSERT_THROW(Robot(model, footprint, State(4, 2)), std::invalid_argument);
  ASSERT_THROW(Robot(model, footprint, State(4, 3)), std::invalid_argument);
}

TEST_F(RobotTest, Accessors) {
  CustomKinematicModel model(3, 2, 5);
  Footprint footprint(footprint_matrix_);
  // Robot with default id.
  Robot robot1{model, footprint};

  VectorXd initial_pose{VectorXd::Random(3)};
  VectorXd initial_velocity{VectorXd::Random(2)};
  VectorXd initial_state(5);
  initial_state << initial_pose, initial_velocity;
  Robot robot2{model, footprint, State(initial_pose, initial_velocity)};

  // Making sure that the initial state is correct.
  // For the robot object created without initial state, the initial pose and
  // velocity must be zero. For the case with an explicit initial state, it must
  // match the given initial state.
  ASSERT_TRUE(
      robot1.get_state().get_data().isApprox(VectorXd::Zero(5)));
  ASSERT_TRUE(robot1.get_pose().get_data().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(
      robot1.get_velocity().get_data().isApprox(VectorXd::Zero(2)));

  ASSERT_TRUE(robot2.get_state().get_data().isApprox(initial_state));
  ASSERT_TRUE(robot2.get_state().get_pose_data().isApprox(initial_pose));
  ASSERT_TRUE(
      robot2.get_state().get_velocity_data().isApprox(initial_velocity));
}

TEST_F(RobotTest, SetState) {
  CustomKinematicModel model(3, 2, 5);
  Footprint footprint(footprint_matrix_);
  Robot robot1{model, footprint};

  VectorXd pose_vector = VectorXd::Random(3);
  VectorXd velocity_vector = VectorXd::Random(2);

  robot1.set_state(State(VectorXd::Ones(3), VectorXd::Ones(2)));
  ASSERT_TRUE(
      robot1.get_state().get_data().isApprox(VectorXd::Ones(5)));

  robot1.set_pose(Pose(pose_vector));
  ASSERT_TRUE(robot1.get_pose().get_data().isApprox(pose_vector));
  // Making sure that the velocity has not changed.
  ASSERT_TRUE(
      robot1.get_velocity().get_data().isApprox(VectorXd::Ones(2)));

  robot1.set_velocity(Velocity(velocity_vector));
  // Making sure that the pose has not changed.
  ASSERT_TRUE(robot1.get_pose().get_data().isApprox(pose_vector));
  ASSERT_TRUE(
      robot1.get_velocity().get_data().isApprox(velocity_vector));

  // Test invalid state, pose and velocity setting.
  ASSERT_THROW(robot1.set_state(State(4, 2)), std::invalid_argument);
  ASSERT_THROW(robot1.set_state(State(3, 3)), std::invalid_argument);
  ASSERT_THROW(robot1.set_state(State(4, 3)), std::invalid_argument);
  ASSERT_THROW(robot1.set_state(State(VectorXd::Zero(2), VectorXd::Zero(2))),
               std::invalid_argument);
  ASSERT_THROW(robot1.set_state(State(VectorXd::Zero(3), VectorXd::Zero(1))),
               std::invalid_argument);
  ASSERT_THROW(robot1.set_state(State(VectorXd::Zero(2), VectorXd::Zero(1))),
               std::invalid_argument);

  ASSERT_THROW(robot1.set_pose(Pose(2)), std::invalid_argument);
  ASSERT_THROW(robot1.set_pose(Pose(VectorXd::Zero(5))), std::invalid_argument);

  ASSERT_THROW(robot1.set_velocity(Velocity(1)), std::invalid_argument);
  ASSERT_THROW(robot1.set_velocity(Velocity(VectorXd::Zero(3))),
               std::invalid_argument);
}

TEST_F(RobotTest, Derivative) {
  CustomKinematicModel model(3, 2, 5);
  Footprint footprint(footprint_matrix_);
  VectorXd initial_pose(3), initial_velocity(2), input(5),
      expected_state_derivative1(5), expected_state_derivative2(5);

  initial_pose << 1, 1, -2;
  initial_velocity << 3, -5;
  input << 1, 2, 3, 2, 1;
  expected_state_derivative1 << 0, 1, -4, 3, 0;

  Robot robot{model, footprint, State(initial_pose, initial_velocity)};

  // Testing derivative computation.
  State derivative1 = robot.ComputeStateDerivative(input);

  ASSERT_TRUE(
      derivative1.get_data().isApprox(expected_state_derivative1));

  expected_state_derivative2 << 0, 1, 2, 1, 0;

  // Testing derivative computation for a different state.
  State derivative2 = robot.ComputeStateDerivative(
      State(VectorXd::Ones(3), VectorXd::Ones(2)), input);

  ASSERT_TRUE(
      derivative2.get_data().isApprox(expected_state_derivative2));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

