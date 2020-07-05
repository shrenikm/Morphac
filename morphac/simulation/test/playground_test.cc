#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/diffdrive_model.h"
#include "simulation/include/playground.h"

namespace {

using std::make_unique;
using std::srand;
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
using morphac::simulation::PlaygroundSpec;
using morphac::simulation::PlaygroundState;
using morphac::simulation::Playground;

// Global kinematic models as if they're destroyed, the reference to the model
// in Robot points to nothing and we get strange results.
DiffDriveModel diffdrive_model(1., 1.);

// Derived class from Pilot for testing.
class CustomPilot : public Pilot {
 public:
  CustomPilot(VectorXd input_data) : Pilot(), input_data_(input_data) {}

  Input Execute(const PlaygroundState& playground_state,
                const int uid) override {
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
    robot2_ =
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
                        IntegratorType::kEulerIntegrator, 0);

  // Test if the robot has been added. As this is playground's AddRobot
  // interface, we also test if the correct robot has been added by checking
  // the initial state
  ASSERT_EQ(playground_->get_state().NumRobots(), 1);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

