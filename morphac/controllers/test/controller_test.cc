#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/control_input.h"
#include "controllers/include/controller.h"

namespace {

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::controllers::Controller;

// Derived Controller class for testing.
class CustomController : public Controller {
 public:
  CustomController(VectorXd control_input_data)
      : Controller(), control_input_data_(control_input_data) {}

  // ControlInput computation that always returns the same control input.
  ControlInput Compute() { return ControlInput(control_input_data_); }

 private:
  VectorXd control_input_data_;
};

class ControllerTest : public ::testing::Test {
 protected:
  ControllerTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
};

TEST_F(ControllerTest, Construction) {
  VectorXd control_input_data1 = VectorXd::Random(1);
  VectorXd control_input_data2 = VectorXd::Random(6);
  CustomController controller1{control_input_data1};
  CustomController controller2{control_input_data2};
}

TEST_F(ControllerTest, Compute) {
  VectorXd control_input_data1 = VectorXd::Random(1);
  VectorXd control_input_data2 = VectorXd::Random(6);
  CustomController controller1{control_input_data1};
  CustomController controller2{control_input_data2};

  ASSERT_TRUE(controller1.Compute().get_data().isApprox(control_input_data1));
  ASSERT_TRUE(controller2.Compute().get_data().isApprox(control_input_data2));
}

}  // namespace
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
