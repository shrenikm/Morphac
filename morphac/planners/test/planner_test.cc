#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/control_input.h"
#include "planners/include/planner.h"

namespace {

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::planners::Planner;

// Derived Planner class for testing.
class CustomPlanner : public Planner {
 public:
  CustomPlanner(VectorXd control_input_data)
      : Planner(), control_input_data_(control_input_data) {}

  // ControlInput computation that always returns the same control input.
  ControlInput Compute() { return ControlInput(control_input_data_); }

 private:
  VectorXd control_input_data_;
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
  VectorXd control_input_data1 = VectorXd::Random(1);
  VectorXd control_input_data2 = VectorXd::Random(6);
  CustomPlanner planner1{control_input_data1};
  CustomPlanner planner2{control_input_data2};
}

TEST_F(PlannerTest, Compute) {
  VectorXd control_input_data1 = VectorXd::Random(1);
  VectorXd control_input_data2 = VectorXd::Random(6);
  CustomPlanner planner1{control_input_data1};
  CustomPlanner planner2{control_input_data2};

  ASSERT_TRUE(planner1.Compute().get_data().isApprox(control_input_data1));
  ASSERT_TRUE(planner2.Compute().get_data().isApprox(control_input_data2));
}

}  // namespace
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
