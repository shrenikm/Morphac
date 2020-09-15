#include "controllers/basic/include/constant_controller.h"

#include "Eigen/Dense"
#include "constructs/include/control_input.h"
#include "gtest/gtest.h"

namespace {

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::controllers::basic::ConstantController;

class ConstantControllerTest : public ::testing::Test {
 protected:
  ConstantControllerTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
};

TEST_F(ConstantControllerTest, Construction) {
  ConstantController controller1{VectorXd::Random(1)};
  ConstantController controller2{VectorXd::Random(6)};
}

TEST_F(ConstantControllerTest, InvalidConstruction) {
  ASSERT_THROW(ConstantController(VectorXd::Random(0)), std::invalid_argument);
}

TEST_F(ConstantControllerTest, Compute) {
  VectorXd control_input_data1 = VectorXd::Random(1);
  VectorXd control_input_data2 = VectorXd::Random(6);
  ConstantController controller1{control_input_data1};
  ConstantController controller2{control_input_data2};

  ASSERT_TRUE(controller1.Compute().get_data().isApprox(control_input_data1));
  ASSERT_TRUE(controller2.Compute().get_data().isApprox(control_input_data2));
}

}  // namespace
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
