#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/trajectory.h"
#include "planners/include/planner.h"

namespace {

using Eigen::MatrixXd;

using morphac::constructs::Trajectory;
using morphac::planners::Planner;

// Derived Planner class for testing.
class CustomPlanner : public Planner {
 public:
  CustomPlanner(MatrixXd trajectory_data, int pose_size, int velocity_size)
      : Planner(), trajectory_(trajectory_data, pose_size, velocity_size) {}

  // ControlInput computation that always returns the same control input.
  Trajectory Compute() { return trajectory_; }

 private:
  Trajectory trajectory_;
};

class PlannerTest : public ::testing::Test {
 protected:
  PlannerTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
};

TEST_F(PlannerTest, Construction) {
  MatrixXd trajectory_data1 = MatrixXd::Random(1, 5);
  MatrixXd trajectory_data2 = MatrixXd::Random(60, 6);
  CustomPlanner planner1{trajectory_data1, 3, 2};
  CustomPlanner planner2{trajectory_data2, 2, 4};
}

TEST_F(PlannerTest, Compute) {
  MatrixXd trajectory_data1 = MatrixXd::Random(1, 5);
  MatrixXd trajectory_data2 = MatrixXd::Random(60, 6);
  CustomPlanner planner1{trajectory_data1, 3, 2};
  CustomPlanner planner2{trajectory_data2, 2, 4};

  ASSERT_TRUE(planner1.Compute().get_data().isApprox(trajectory_data1));
  ASSERT_TRUE(planner2.Compute().get_data().isApprox(trajectory_data2));
}

}  // namespace
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
