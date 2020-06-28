#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "environments/include/environment.h"

namespace {

using std::make_unique;
using std::unique_ptr;

using Eigen::MatrixXd;

using morphac::environments::Environment;

class EnvironmentTest : public ::testing::Test {
 protected:
  EnvironmentTest() {
    // Set random seed for Eigen.
    srand(7);
    env1_ = make_unique<Environment>(10, 10, 0.01);
    env2_ = make_unique<Environment>(MatrixXd::Random(500, 500), 0.01);
  }

  void SetUp() override {}

  unique_ptr<Environment> env1_, env2_;
};

TEST_F(EnvironmentTest, CopyConstruction) {
  Environment env1(*env1_);

  Environment env2(20, 30, 0.1);
  Environment env3(env2);

  ASSERT_EQ(env3.get_width(), 20);
  ASSERT_EQ(env3.get_height(), 30);
  ASSERT_EQ(env3.get_resolution(), 0.1);
}

TEST_F(EnvironmentTest, CopyAssignment) {
  Environment env1 = *env1_;

  Environment env2(20, 30, 0.1);
  Environment env3 = env2;

  ASSERT_EQ(env3.get_width(), 20);
  ASSERT_EQ(env3.get_height(), 30);
  ASSERT_EQ(env3.get_resolution(), 0.1);
}

TEST_F(EnvironmentTest, InvalidConstruction) {
  ASSERT_THROW(Environment(-1, -2, 0.01), std::invalid_argument);
  ASSERT_THROW(Environment(1, 0, 0.01), std::invalid_argument);
  ASSERT_THROW(Environment(0, 2, 0.01), std::invalid_argument);
  ASSERT_THROW(Environment(1, 2, -0.01), std::invalid_argument);

  ASSERT_THROW(Environment(MatrixXd::Random(0, 100), 0.01),
               std::invalid_argument);
  ASSERT_THROW(Environment(MatrixXd::Random(100, 0), 0.01),
               std::invalid_argument);
  ASSERT_THROW(Environment(MatrixXd::Random(0, 0), 0.01),
               std::invalid_argument);
  ASSERT_THROW(Environment(MatrixXd::Random(200, 100), -0.01),
               std::invalid_argument);

  // Constructing with an invalid resolution.
  ASSERT_THROW(Environment(10, 9.4, 0.123), std::invalid_argument);
  ASSERT_THROW(Environment(10, 9.12, 0.0489), std::invalid_argument);
  // While creating the environment with a data, the resolution is always right
  // as the width and height are computed from the data and resolution and the
  // data is always valid dimension wise. Hence we don't test it.
}

TEST_F(EnvironmentTest, Accessors) {
  Environment env1{10, 9.5, 0.01};
  MatrixXd data = MatrixXd::Random(480, 640);
  Environment env2{data, 0.02};

  ASSERT_EQ(env1.get_width(), 10);
  ASSERT_EQ(env1.get_height(), 9.5);
  ASSERT_EQ(env1.get_resolution(), 0.01);
  ASSERT_TRUE(env1.get_data().isApprox(MatrixXd::Zero(950, 1000)));

  ASSERT_EQ(env2.get_width(), 12.8);
  ASSERT_EQ(env2.get_height(), 9.6);
  ASSERT_EQ(env2.get_resolution(), 0.02);
  ASSERT_TRUE(env2.get_data().isApprox(data));

  // Setting a different data.
  data = MatrixXd::Random(480, 640);
  env2.set_data(data);

  ASSERT_EQ(env2.get_width(), 12.8);
  ASSERT_EQ(env2.get_height(), 9.6);
  ASSERT_EQ(env2.get_resolution(), 0.02);
  ASSERT_TRUE(env2.get_data().isApprox(data));

  // Setting an invalid data.
  ASSERT_THROW(env2.set_data(MatrixXd::Random(0, 0)), std::invalid_argument);
  ASSERT_THROW(env2.set_data(MatrixXd::Random(640, 480)), std::invalid_argument);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
