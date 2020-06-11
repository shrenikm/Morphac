#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "robot/blueprint/include/footprint.h"

namespace {

using Eigen::MatrixXd;

using morphac::robot::blueprint::Footprint;

class FootprintTest : public ::testing::Test {
 protected:
  FootprintTest() {
    // Set random seed for Eigen.
    srand(7);
    footprint_matrix_ = MatrixXd::Random(10, 2);
  }

  void SetUp() override {}

  MatrixXd footprint_matrix_;
};

TEST_F(FootprintTest, Construction) { Footprint footprint(footprint_matrix_); }

TEST_F(FootprintTest, Accessors) {
  Footprint footprint(footprint_matrix_);
  ASSERT_TRUE(footprint.get_footprint_matrix().isApprox(footprint_matrix_));
}

TEST_F(FootprintTest, InvalidConstruction) {
  ASSERT_THROW(Footprint(MatrixXd::Zero(0, 0)), std::invalid_argument);
  ASSERT_THROW(Footprint(MatrixXd::Zero(0, 2)), std::invalid_argument);
  ASSERT_THROW(Footprint(MatrixXd::Zero(4, 3)), std::invalid_argument);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
