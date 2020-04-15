#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "robot/blueprint/include/footprint2D.h"

namespace {

using Eigen::MatrixXd;

using morphac::robot::blueprint::Footprint2D;

class Footprint2DTest : public ::testing::Test {
 protected:
  Footprint2DTest() {}

  void SetUp() override { footprint_matrix_ = MatrixXd::Random(10, 2); }

  MatrixXd footprint_matrix_;
};

TEST_F(Footprint2DTest, Construction) {
  Footprint2D footprint(footprint_matrix_);
}

TEST_F(Footprint2DTest, Accessors) {
  Footprint2D footprint(footprint_matrix_);
  ASSERT_TRUE(footprint.get_footprint_matrix().isApprox(footprint_matrix_));
}

TEST_F(Footprint2DTest, InvalidConstruction) {
  ASSERT_THROW(Footprint2D(MatrixXd::Zero(0, 0)), std::invalid_argument);
  ASSERT_THROW(Footprint2D(MatrixXd::Zero(0, 2)), std::invalid_argument);
  ASSERT_THROW(Footprint2D(MatrixXd::Zero(4, 3)), std::invalid_argument);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
