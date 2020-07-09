#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/diffdrive_model.h"
#include "simulation/playground/include/playground.h"

namespace {

using std::make_unique;
using std::srand;
using std::sqrt;
using std::unique_ptr;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::environment::Map;
using morphac::mechanics::models::DiffDriveModel;
using morphac::math::numeric::IntegratorType;
using morphac::robot::blueprint::Footprint;
using morphac::robot::blueprint::Robot;
using morphac::robot::driver::Pilot;
using morphac::simulation::playground::PlaygroundSpec;
using morphac::simulation::playground::PlaygroundState;
using morphac::simulation::playground::Playground;

// Global kinematic models as if they're destroyed, the reference to the model
// in Robot points to nothing and we get strange results.
DiffDriveModel diffdrive_model(1., 1.);

// Derived class from Pilot for testing.
class CustomPilot : public Pilot {
 public:
  CustomPilot(VectorXd input_data) : Pilot(), input_data_(input_data) {}

  Input Execute(const PlaygroundState& playground_state,
                const int uid) const override {
    // Some asserts to prevent the unused variable warning.
    MORPH_REQUIRE(playground_state.NumRobots() >= 0, std::invalid_argument,
                  "Invalid PlaygroundState");
    MORPH_REQUIRE(uid >= 0, std::invalid_argument, "UID must be non negative");
    return Input(input_data_);
  }

 private:
  VectorXd input_data_;
};

class PlaygroundTest : public ::testing::Test {
 protected:
  PlaygroundTest() {
    // Set random seed for Eigen.
    srand(7);

    robot1_ =
        make_unique<Robot>(diffdrive_model, Footprint(MatrixXd::Zero(20, 2)));
    robot2_ =
        make_unique<Robot>(diffdrive_model, Footprint(MatrixXd::Zero(20, 2)),
                           State({1., 2., 0.}, {}));
    robot3_ =
        make_unique<Robot>(diffdrive_model, Footprint(MatrixXd::Zero(20, 2)),
                           State({-5., 7., 1.57}, {}));
    playground_ =
        make_unique<Playground>(playground_spec_, Map(map_data_, 0.1));
  }

  void SetUp() override {}

  unique_ptr<Playground> playground_;
  unique_ptr<Robot> robot1_, robot2_, robot3_;
  MatrixXd map_data_ = MatrixXd::Random(20, 10);
  PlaygroundSpec playground_spec_{"playground", 0.05, 640, 480};
};

TEST_F(PlaygroundTest, GetState) {
  // Making sure that we get can get the correct state from the playground.
  PlaygroundState& playground_state = playground_->get_state();

  ASSERT_TRUE(playground_state.get_map().get_data().isApprox(map_data_));
  ASSERT_EQ(playground_state.NumRobots(), 0);

  // Making sure that the state reference works correctly. If we change the
  // value of the state through the reference, it should reflect back in the
  // state stored by the Playground.

  MatrixXd new_map_data = MatrixXd::Random(20, 10);
  Map new_map{new_map_data, 0.1};
  playground_state.set_map(new_map);

  ASSERT_TRUE(
      playground_->get_state().get_map().get_data().isApprox(new_map_data));

  // Testing adding robots.
  // We only check the number of robots in the state. Addition of the correct
  // robots against the uids is checked by the PlaygroundState test.
  playground_state.AddRobot(*robot1_, 0);
  ASSERT_EQ(playground_->get_state().NumRobots(), 1);

  // Adding the other two robots.
  playground_state.AddRobot(*robot2_, 1);
  playground_state.AddRobot(*robot3_, 2);
  ASSERT_EQ(playground_->get_state().NumRobots(), 3);
}

TEST_F(PlaygroundTest, AddRobot) {
  // Add the first robot.
  playground_->AddRobot(*robot1_, CustomPilot(VectorXd::Zero(3)),
                        IntegratorType::kEulerIntegrator, 1);

  // Test if the robot has been added. As this is playground's AddRobot
  // interface, we also test if the correct robot has been added by checking
  // the initial state
  ASSERT_EQ(playground_->get_state().NumRobots(), 1);
  ASSERT_TRUE(
      playground_->get_state().get_robot(1).get_state().get_data().isApprox(
          VectorXd::Zero(3)));

  // Adding the other robots.
  // Initial state vectors for the other robots.
  VectorXd initial_state_data1(3), initial_state_data2(3);
  initial_state_data1 << 1., 2., 0.;
  initial_state_data2 << -5., 7., 1.57;

  playground_->AddRobot(*robot2_, CustomPilot(VectorXd::Ones(3)),
                        IntegratorType::kMidPointIntegrator, 2);
  playground_->AddRobot(*robot3_, CustomPilot(VectorXd::Random(3)),
                        IntegratorType::kRK4Integrator, 3);

  ASSERT_EQ(playground_->get_state().NumRobots(), 3);
  ASSERT_TRUE(
      playground_->get_state().get_robot(2).get_state().get_data().isApprox(
          initial_state_data1));
  ASSERT_TRUE(
      playground_->get_state().get_robot(3).get_state().get_data().isApprox(
          initial_state_data2));
}

TEST_F(PlaygroundTest, InvalidAddRobot) {
  // Add the first robot.
  playground_->AddRobot(*robot1_, CustomPilot(VectorXd::Zero(3)),
                        IntegratorType::kEulerIntegrator, 7);

  // Add the other robots with invalid uids.
  // Negative uid.
  ASSERT_THROW(playground_->AddRobot(*robot2_, CustomPilot(VectorXd::Zero(3)),
                                     IntegratorType::kMidPointIntegrator, -1),
               std::logic_error);
  // Duplicate uid.
  ASSERT_THROW(playground_->AddRobot(*robot3_, CustomPilot(VectorXd::Zero(3)),
                                     IntegratorType::kRK4Integrator, 7),
               std::logic_error);
}

TEST_F(PlaygroundTest, Execute) {
  // Add Robots.
  CustomPilot pilot1{VectorXd::Zero(2)};
  CustomPilot pilot2{VectorXd::Ones(2)};
  CustomPilot pilot3{3 * VectorXd::Ones(2)};

  playground_->AddRobot(*robot1_, pilot1, IntegratorType::kRK4Integrator, 1);
  // Change the initial state of the second robot.
  robot2_->set_state(State({1., 2., 0.}, {}));
  // The pilot drives both wheels at the same velocity.
  playground_->AddRobot(*robot2_, pilot2, IntegratorType::kRK4Integrator, 2);

  // Changing the intial state of the last robot. It points at a 45 degree
  // angle.
  robot3_->set_state(State({-5., -7., M_PI / 4}, {}));
  // Constant velocities on both wheels.
  playground_->AddRobot(*robot3_, pilot3, IntegratorType::kRK4Integrator, 3);

  // Executing and testing if the new states of the robots after a dt step
  // is correct.
  playground_->Execute();

  //// Initializing expected state data.
  VectorXd expected_state_data1(3), expected_state_data2(3),
      expected_state_data3(3);
  expected_state_data1 << 0., 0., 0.;
  // As the wheel radius is 1. and the angular velocities are 1., the robot
  // moves forward along a straight line at a speed of 1 m/s. As dt is 0.05,
  // it covers a net distance of 0.05 meters. It only moves along the x axis as
  // it is facing this direction.
  expected_state_data2 << 1.05, 2., 0.;
  // For the last case, the robot moves forward at a speed of 3 m/s, thus
  // covering a distance of 3 * 0.05 = 0.15 m. In this case, the robot is at
  // a 45 degree angle and thus moves along x and y.
  expected_state_data3 << -5. + (0.15 / sqrt(2)), -7. + (0.15 / sqrt(2)),
      M_PI / 4;

  ASSERT_TRUE(playground_->get_state().get_robot_state(1).get_data().isApprox(
      expected_state_data1));
  ASSERT_TRUE(playground_->get_state().get_robot_state(2).get_data().isApprox(
      expected_state_data2));
  ASSERT_TRUE(playground_->get_state().get_robot_state(3).get_data().isApprox(
      expected_state_data3));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

