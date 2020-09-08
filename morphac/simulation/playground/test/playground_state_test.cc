#include "simulation/playground/include/playground_state.h"

#include "Eigen/Dense"
#include "gtest/gtest.h"
#include "mechanics/models/include/diffdrive_model.h"

namespace {

using std::make_unique;
using std::srand;
using std::unique_ptr;

using Eigen::MatrixXd;

using morphac::constructs::State;
using morphac::environment::Map;
using morphac::mechanics::models::DiffdriveModel;
using morphac::mechanics::models::KinematicModel;
using morphac::robot::blueprint::Footprint;
using morphac::robot::blueprint::Robot;
using morphac::simulation::playground::PlaygroundState;

// Global kinematic models as if they're destroyed, the reference to the model
// in Robot points to nothing and we get strange results.
DiffdriveModel diffdrive_model1(1., 1.);
DiffdriveModel diffdrive_model2(2., 2.);

class PlaygroundStateTest : public ::testing::Test {
 protected:
  PlaygroundStateTest() {
    // Set random seed for Eigen.
    srand(7);

    playground_state1_ = make_unique<PlaygroundState>(Map(40, 20, 0.1));
    playground_state2_ = make_unique<PlaygroundState>(Map(map_data_, 0.1));
    robot1_ =
        make_unique<Robot>(diffdrive_model1, Footprint(MatrixXd::Zero(10, 2)));
    robot2_ =
        make_unique<Robot>(diffdrive_model2, Footprint(MatrixXd::Ones(10, 2)));
  }

  void SetUp() override {}

  unique_ptr<PlaygroundState> playground_state1_, playground_state2_;
  unique_ptr<Robot> robot1_, robot2_;
  MatrixXd map_data_ = MatrixXd::Random(300, 300);
};

TEST_F(PlaygroundStateTest, GetTime) {
  ASSERT_EQ(playground_state1_->get_time(), 0);
  ASSERT_EQ(playground_state2_->get_time(), 0);
}

TEST_F(PlaygroundStateTest, SetTime) {
  playground_state1_->set_time(0.005);
  playground_state2_->set_time(15.7);
  ASSERT_EQ(playground_state1_->get_time(), 0.005);
  ASSERT_EQ(playground_state2_->get_time(), 15.7);
}

TEST_F(PlaygroundStateTest, GetMap) {
  ASSERT_TRUE(playground_state1_->get_map().get_data().isApprox(
      MatrixXd::Zero(200, 400)));
  ASSERT_EQ(playground_state1_->get_map().get_width(), 40.);
  ASSERT_EQ(playground_state1_->get_map().get_height(), 20.);
  ASSERT_EQ(playground_state1_->get_map().get_resolution(), 0.1);

  ASSERT_TRUE(playground_state2_->get_map().get_data().isApprox(map_data_));
  ASSERT_EQ(playground_state2_->get_map().get_width(), 30.);
  ASSERT_EQ(playground_state2_->get_map().get_height(), 30.);
  ASSERT_EQ(playground_state2_->get_map().get_resolution(), 0.1);
}

TEST_F(PlaygroundStateTest, SetMap) {
  MatrixXd map_data = MatrixXd::Random(400, 200);
  playground_state1_->set_map(Map(map_data, 0.1));
  ASSERT_TRUE(playground_state1_->get_map().get_data().isApprox(map_data));

  playground_state2_->set_map(Map(30., 30., 0.1));
  ASSERT_TRUE(playground_state2_->get_map().get_data().isApprox(
      MatrixXd::Zero(300, 300)));
}

TEST_F(PlaygroundStateTest, AddRobot) {
  // Also testing NumRobots.
  playground_state1_->AddRobot(*robot1_, 0);
  ASSERT_EQ(playground_state1_->NumRobots(), 1);

  playground_state2_->AddRobot(*robot1_, 0);
  playground_state2_->AddRobot(*robot2_, 1);
  ASSERT_EQ(playground_state2_->NumRobots(), 2);
}

TEST_F(PlaygroundStateTest, InvalidAddRobot) {
  // Add robot with invalid UIDs
  ASSERT_THROW(playground_state1_->AddRobot(*robot1_, -1),
               std::invalid_argument);

  // Add robot with duplicate UIDs
  playground_state2_->AddRobot(*robot1_, 0);
  ASSERT_THROW(playground_state2_->AddRobot(*robot2_, 0),
               std::invalid_argument);

  // It should be possible to add the same robot object multiple times.
  playground_state2_->AddRobot(*robot1_, 1);
}

TEST_F(PlaygroundStateTest, GetRobotOracle) {
  // Adding robots.
  playground_state1_->AddRobot(*robot1_, 0);
  playground_state1_->AddRobot(*robot2_, 2);

  auto robot_oracle = playground_state1_->get_robot_oracle();

  // Making sure that the oracle has the right size
  ASSERT_EQ(robot_oracle.size(), 2);

  // Testing actual contents of the oracle. It must store the right robots
  // against the right uids
  const DiffdriveModel& model1 =
      dynamic_cast<const DiffdriveModel&>(robot1_->get_kinematic_model());
  const DiffdriveModel& model2 =
      dynamic_cast<const DiffdriveModel&>(robot2_->get_kinematic_model());

  // Testing values of the first robot.
  ASSERT_EQ(model1.pose_size, 3);
  ASSERT_EQ(model1.velocity_size, 0);
  ASSERT_EQ(model1.control_input_size, 2);
  ASSERT_EQ(model1.width, 1.);
  ASSERT_EQ(model1.radius, 1.);
  ASSERT_TRUE(robot_oracle.find(0)->second.get_footprint().get_data().isZero());

  // Testing values for the second robot.
  ASSERT_EQ(model2.pose_size, 3);
  ASSERT_EQ(model2.velocity_size, 0);
  ASSERT_EQ(model2.control_input_size, 2);
  ASSERT_EQ(model2.width, 2.);
  ASSERT_EQ(model2.radius, 2.);
  ASSERT_TRUE(robot_oracle.find(2)->second.get_footprint().get_data().isOnes());

  // Make sure that if the uid is invalid, we cannot find it in the oracle.
  ASSERT_EQ(robot_oracle.find(-1), robot_oracle.end());
  ASSERT_EQ(robot_oracle.find(3), robot_oracle.end());
}

TEST_F(PlaygroundStateTest, GetRobot) {
  // Adding robots.
  playground_state1_->AddRobot(*robot1_, 1);
  playground_state1_->AddRobot(*robot2_, 2);

  auto robot1 = playground_state1_->get_robot(1);
  auto robot2 = playground_state1_->get_robot(2);

  // Getting the downcasted models.
  const DiffdriveModel& model1 =
      dynamic_cast<const DiffdriveModel&>(robot1_->get_kinematic_model());
  const DiffdriveModel& model2 =
      dynamic_cast<const DiffdriveModel&>(robot2_->get_kinematic_model());

  // Verifying the robots.
  ASSERT_EQ(robot1.get_kinematic_model().pose_size, 3);
  ASSERT_EQ(robot1.get_kinematic_model().velocity_size, 0);
  ASSERT_EQ(robot1.get_kinematic_model().control_input_size, 2);
  ASSERT_EQ(model1.width, 1.);
  ASSERT_EQ(model1.radius, 1.);
  ASSERT_TRUE(robot1.get_footprint().get_data().isZero());

  ASSERT_EQ(robot2.get_kinematic_model().pose_size, 3);
  ASSERT_EQ(robot2.get_kinematic_model().velocity_size, 0);
  ASSERT_EQ(robot2.get_kinematic_model().control_input_size, 2);
  ASSERT_EQ(model2.width, 2.);
  ASSERT_EQ(model2.radius, 2.);
  ASSERT_TRUE(robot2.get_footprint().get_data().isOnes());

  // Calling the function with an invalid id must throw an exception.
  ASSERT_THROW(playground_state1_->get_robot(-1), std::invalid_argument);
  ASSERT_THROW(playground_state1_->get_robot(0), std::invalid_argument);
  ASSERT_THROW(playground_state1_->get_robot(3), std::invalid_argument);
}

TEST_F(PlaygroundStateTest, GetRobotState) {
  // Adding robots.
  // Changing the state.
  State new_state({-1., 2., 1.57}, {});
  robot2_->set_state(new_state);
  playground_state1_->AddRobot(*robot1_, 1);
  playground_state1_->AddRobot(*robot2_, 2);

  ASSERT_EQ(playground_state1_->get_robot_state(1), State(3, 0));
  ASSERT_EQ(playground_state1_->get_robot_state(2), new_state);
}

TEST_F(PlaygroundStateTest, SetRobotState) {
  // Adding robots.
  playground_state1_->AddRobot(*robot1_, 1);
  playground_state1_->AddRobot(*robot2_, 2);

  // Initial robot states.
  ASSERT_EQ(playground_state1_->get_robot_state(1), State(3, 0));
  ASSERT_EQ(playground_state1_->get_robot_state(2), State(3, 0));

  // Changing the robot states through the playground states.
  State new_state1({1., 2., 3.}, {});
  State new_state2({0., -5., 0.1}, {});

  playground_state1_->set_robot_state(new_state1, 1);
  playground_state1_->set_robot_state(new_state2, 2);

  ASSERT_EQ(playground_state1_->get_robot_state(1), new_state1);
  ASSERT_EQ(playground_state1_->get_robot_state(2), new_state2);

  // If we try setting the state for an invalid id, it should throw an error.
  ASSERT_THROW(playground_state1_->set_robot_state(State(3, 0), 0),
               std::invalid_argument);
  ASSERT_THROW(playground_state1_->set_robot_state(State(3, 0), 3),
               std::invalid_argument);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
