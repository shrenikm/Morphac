#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "robot/pilot/include/pilot.h"

namespace {

using Eigen::VectorXd;
using Eigen::MatrixXd;

using morphac::constructs::ControlInput;
using morphac::environment::Map;
using morphac::robot::pilot::Pilot;
using morphac::simulation::playground::PlaygroundState;

// Derived Pilot class for testing.
class CustomPilot : public Pilot {
 public:
  CustomPilot(VectorXd control_input_data)
      : Pilot(), control_input_data_(control_input_data) {}

  ControlInput Execute(const PlaygroundState& playground_state,
                       const int uid) const override {
    // Some asserts to prevent the unused variable warning.
    MORPH_REQUIRE(playground_state.NumRobots() >= 0, std::invalid_argument,
                  "Invalid PlaygroundState");
    MORPH_REQUIRE(uid >= 0, std::invalid_argument, "UID must be non negative");
    return ControlInput(control_input_data_);
  }

 private:
  VectorXd control_input_data_;
};

class PilotTest : public ::testing::Test {
 protected:
  PilotTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
};

TEST_F(PilotTest, Construction) {
  VectorXd control_input_data1 = VectorXd::Random(3);
  VectorXd control_input_data2 = VectorXd::Random(16);
  CustomPilot pilot1{control_input_data1};
  CustomPilot pilot2{control_input_data2};
}

TEST_F(PilotTest, Execute) {
  VectorXd control_input_data1 = VectorXd::Random(3);
  VectorXd control_input_data2 = VectorXd::Random(16);
  CustomPilot pilot1{control_input_data1};
  CustomPilot pilot2{control_input_data2};

  // Creating a sample playground state.
  PlaygroundState playground_state{Map(MatrixXd::Zero(300, 300), 0.1)};

  ASSERT_TRUE(pilot1.Execute(playground_state, 0)
                  .get_data()
                  .isApprox(control_input_data1));
  ASSERT_TRUE(pilot2.Execute(playground_state, 1)
                  .get_data()
                  .isApprox(control_input_data2));
}

}  // namespace
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
