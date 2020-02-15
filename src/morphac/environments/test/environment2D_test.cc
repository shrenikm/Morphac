#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "environments/include/environment2D.h"

namespace {

using Eigen::MatrixXd;

using morphac::environments::Environment2D;

class Environment2DTest : public ::testing::Test {
 protected:
  Environment2DTest() {}

  void SetUp() override {}
};

TEST_F(Environment2DTest, Construction) {
  Environment2D env1{10, 10, 0.01};
  Environment2D env2{MatrixXd::Random(500, 500), 0.01};
}

TEST_F(Environment2DTest, InvalidConstruction) {
  ASSERT_THROW(Environment2D(-1, -2, 0.01), std::invalid_argument);
  ASSERT_THROW(Environment2D(1, 0, 0.01), std::invalid_argument);
  ASSERT_THROW(Environment2D(0, 2, 0.01), std::invalid_argument);
  ASSERT_THROW(Environment2D(1, 2, -0.01), std::invalid_argument);

  ASSERT_THROW(Environment2D(MatrixXd::Random(0, 100), 0.01),
               std::invalid_argument);
  ASSERT_THROW(Environment2D(MatrixXd::Random(100, 0), 0.01),
               std::invalid_argument);
  ASSERT_THROW(Environment2D(MatrixXd::Random(0, 0), 0.01),
               std::invalid_argument);
  ASSERT_THROW(Environment2D(MatrixXd::Random(200, 100), -0.01),
               std::invalid_argument);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
