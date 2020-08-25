#include "gtest/gtest.h"

#include "utils/include/points_utils.h"

namespace {

using std::sqrt;

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::VectorXd;

using morphac::common::aliases::HomogeneousPoints;
using morphac::common::aliases::Points;
using morphac::utils::HomogenizePoints;
using morphac::utils::UnHomogenizePoints;

class TransformsUtilsTest : public ::testing::Test {
 protected:
  TransformsUtilsTest() {
    // Set random seed for Eigen.
    srand(7);

    points_ = Points::Random(10, 2);
  }

  void SetUp() override {}

  Points points_;
};

TEST_F(TransformsUtilsTest, HomogenizePoints) {
  HomogeneousPoints homogenous_points = HomogenizePoints(points_);

  ASSERT_TRUE(homogenous_points.col(0).isApprox(points_.col(0)));
  ASSERT_TRUE(homogenous_points.col(1).isApprox(points_.col(1)));
  ASSERT_TRUE(homogenous_points.col(2).isApprox(VectorXd::Ones(10)));
}

TEST_F(TransformsUtilsTest, UnHomogenizePoints) {
  HomogeneousPoints homogenous_points = HomogenizePoints(points_);
  Points recovered_points = UnHomogenizePoints(homogenous_points);

  ASSERT_TRUE(recovered_points.isApprox(points_));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
