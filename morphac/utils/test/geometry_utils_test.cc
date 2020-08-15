#include "gtest/gtest.h"

#include "utils/include/geometry_utils.h"

namespace {

using std::sqrt;

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::VectorXd;

using morphac::utils::CreateRectangularPolygon;
using morphac::utils::CreateArc;
using morphac::utils::CreateCircularPolygon;
using morphac::utils::CreateRoundedRectangularPolygon;
using morphac::utils::HomogenizePoints;
using morphac::utils::TransformPoints;
using morphac::utils::UnHomogenizePoints;

TEST(GeometryUtilsTest, HomogenizePoints) {
  srand(7);
  Points points = Points::Random(10, 2);

  HomogeneousPoints homogenous_points = HomogenizePoints(points);

  ASSERT_TRUE(homogenous_points.col(0).isApprox(points.col(0)));
  ASSERT_TRUE(homogenous_points.col(1).isApprox(points.col(1)));
  ASSERT_TRUE(homogenous_points.col(2).isApprox(VectorXd::Ones(10)));
}

TEST(GeometryUtilsTest, UnHomogenizePoints) {
  srand(7);
  Points points = Points::Random(20, 2);

  HomogeneousPoints homogenous_points = HomogenizePoints(points);
  Points recovered_points = UnHomogenizePoints(homogenous_points);

  ASSERT_TRUE(recovered_points.isApprox(points));
}

TEST(GeometryUtilsTest, TransformPoints) {
  // A square polygon for testing.
  MatrixXd points(4, 2), rotated_points(4, 2);
  points << -2, 2, 2, 2, 2, -2, -2, -2;
  rotated_points << 0, 2 * sqrt(2), 2 * sqrt(2), 0, 0, -2 * sqrt(2),
      -2 * sqrt(2), 0;
  // Test rotation.
  ASSERT_TRUE(TransformPoints(points, 0., Vector2d::Zero()).isApprox(points));
  ASSERT_TRUE(TransformPoints(points, -M_PI / 4, Vector2d::Zero())
                  .isApprox(rotated_points));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
