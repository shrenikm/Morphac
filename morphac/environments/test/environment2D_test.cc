#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "environments/include/environment2D.h"

namespace {

using std::make_unique;
using std::unique_ptr;

using Eigen::MatrixXd;

using morphac::environments::Environment2D;

class Environment2DTest : public ::testing::Test {
 protected:
  Environment2DTest() {
    // Set random seed for Eigen.
    srand(7);
    env1_ = make_unique<Environment2D>(10, 10, 0.01);
    env2_ = make_unique<Environment2D>(MatrixXd::Random(500, 500), 0.01);
  }

  void SetUp() override {}

  unique_ptr<Environment2D> env1_, env2_;
};

TEST_F(Environment2DTest, CopyConstruction) {
  Environment2D env1(*env1_);

  Environment2D env2(20, 30, 0.1);
  Environment2D env3(env2);

  ASSERT_EQ(env3.get_width(), 20);
  ASSERT_EQ(env3.get_height(), 30);
  ASSERT_EQ(env3.get_resolution(), 0.1);
}

TEST_F(Environment2DTest, CopyAssignment) {
  Environment2D env1 = *env1_;

  Environment2D env2(20, 30, 0.1);
  Environment2D env3 = env2;

  ASSERT_EQ(env3.get_width(), 20);
  ASSERT_EQ(env3.get_height(), 30);
  ASSERT_EQ(env3.get_resolution(), 0.1);
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

  // Constructing with an invalid resolution.
  ASSERT_THROW(Environment2D(10, 9.4, 0.123), std::invalid_argument);
  ASSERT_THROW(Environment2D(10, 9.12, 0.0489), std::invalid_argument);
  // While creating the environment with a map, the resolution is always right
  // as the width and height are computed from the map and resolution and the
  // map is always valid dimension wise. Hence we don't test it.
}

TEST_F(Environment2DTest, Accessors) {
  Environment2D env1{10, 9.5, 0.01};
  MatrixXd map = MatrixXd::Random(480, 640);
  Environment2D env2{map, 0.02};

  ASSERT_EQ(env1.get_width(), 10);
  ASSERT_EQ(env1.get_height(), 9.5);
  ASSERT_EQ(env1.get_resolution(), 0.01);
  ASSERT_TRUE(env1.get_map().isApprox(MatrixXd::Zero(950, 1000)));

  ASSERT_EQ(env2.get_width(), 12.8);
  ASSERT_EQ(env2.get_height(), 9.6);
  ASSERT_EQ(env2.get_resolution(), 0.02);
  ASSERT_TRUE(env2.get_map().isApprox(map));

  // Setting a different map.
  map = MatrixXd::Random(480, 640);
  env2.set_map(map);

  ASSERT_EQ(env2.get_width(), 12.8);
  ASSERT_EQ(env2.get_height(), 9.6);
  ASSERT_EQ(env2.get_resolution(), 0.02);
  ASSERT_TRUE(env2.get_map().isApprox(map));

  // Setting an invalid map.
  ASSERT_THROW(env2.set_map(MatrixXd::Random(0, 0)), std::invalid_argument);
  ASSERT_THROW(env2.set_map(MatrixXd::Random(640, 480)), std::invalid_argument);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
