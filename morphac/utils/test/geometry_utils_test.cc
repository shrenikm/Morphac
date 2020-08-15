#include "gtest/gtest.h"

#include "utils/include/geometry_utils.h"

namespace {

using std::sqrt;

using Eigen::MatrixXd;
using Eigen::Vector2d;

using morphac::utils::TransformPoints;
using morphac::utils::CreateRectangularPolygon;
using morphac::utils::CreateArc;
using morphac::utils::CreateCircularPolygon;
using morphac::utils::CreateRoundedRectangularPolygon;

TEST(GeometryUtilsTest, TransformPoints) {
  // A square polygon for testing.
  MatrixXd points(4, 2), rotated_points(4, 2);
  points << -2, 2, 2, 2, 2, -2, -2, -2;
  rotated_points << 0, sqrt(2), sqrt(2), 0, 0, -sqrt(2), -sqrt(2), 0;
  // Test rotation.
  ASSERT_TRUE(TransformPoints(points, 0., Vector2d::Zero()).isApprox(points));
  ASSERT_TRUE(TransformPoints(points, M_PI / 4, Vector2d::Zero())
                  .isApprox(rotated_points));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
