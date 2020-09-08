#include "controllers/basic/include/zero_controller.h"

#include "Eigen/Dense"
#include "constructs/include/control_input.h"
#include "gtest/gtest.h"

namespace {

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::controllers::basic::ZeroController;

class ZeroControllerTest : public ::testing::Test {
 protected:
  ZeroControllerTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
};

TEST_F(ZeroControllerTest, Construction) {
  ZeroController controller1{1};
  ZeroController controller2{6};
}

TEST_F(ZeroControllerTest, InvalidConstruction) {
  ASSERT_THROW(ZeroController(-1), std::invalid_argument);
  ASSERT_THROW(ZeroController(0), std::invalid_argument);
}

TEST_F(ZeroControllerTest, Compute) {
  ZeroController controller1{1};
  ZeroController controller2{6};

  ASSERT_TRUE(controller1.Compute().get_data().isApprox(VectorXd::Zero(1)));
  ASSERT_TRUE(controller2.Compute().get_data().isApprox(VectorXd::Zero(6)));
}

}  // namespace
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
