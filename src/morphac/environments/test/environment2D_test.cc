#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "environments/include/environment2D.h"

namespace {

using Eigen::MatrixXd;

class Environment2DTest : public ::testing::Test {
 protected:
  Environment2DTest() {}

  void SetUp() override {}
};

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
