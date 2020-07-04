#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "robot/driver/include/pilot.h"

namespace {

using Eigen::VectorXd;
using Eigen::MatrixXd;

using morphac::constructs::Input;
using morphac::environment::Map;
using morphac::robot::driver::Pilot;
using morphac::simulation::PlaygroundState;

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

class PilotTest : public ::testing::Test {
 protected:
  PilotTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
};

TEST_F(PilotTest, Construction) {
  VectorXd input_data1 = VectorXd::Random(3);
  VectorXd input_data2 = VectorXd::Random(16);
  CustomPilot pilot1{input_data1};
  CustomPilot pilot2{input_data2};
}

TEST_F(PilotTest, Execute) {
  VectorXd input_data1 = VectorXd::Random(3);
  VectorXd input_data2 = VectorXd::Random(16);
  CustomPilot pilot1{input_data1};
  CustomPilot pilot2{input_data2};

  // Creating a sample playground state.
  PlaygroundState playground_state{Map(MatrixXd::Zero(300, 300), 0.1)};

  ASSERT_TRUE(
      pilot1.Execute(playground_state, 0).get_data().isApprox(input_data1));
  ASSERT_TRUE(
      pilot2.Execute(playground_state, 1).get_data().isApprox(input_data2));
}

}  // namespace
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

