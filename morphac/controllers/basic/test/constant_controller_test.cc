#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/control_input.h"
#include "controllers/basic/include/constant_controller.h"

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

}  // namespace
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
