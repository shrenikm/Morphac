#include "gtest/gtest.h"

#include "utils/include/transforms_utils.h"

namespace {

using std::sqrt;

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::VectorXd;

using morphac::utils::HomogenizePoints;
using morphac::utils::RotatePoints;
using morphac::utils::TransformPoints;
using morphac::utils::UnHomogenizePoints;

TEST(TransformsUtilsTest, HomogenizePoints) {
  srand(7);
  Points points = Points::Random(10, 2);

  HomogeneousPoints homogenous_points = HomogenizePoints(points);

  ASSERT_TRUE(homogenous_points.col(0).isApprox(points.col(0)));
  ASSERT_TRUE(homogenous_points.col(1).isApprox(points.col(1)));
  ASSERT_TRUE(homogenous_points.col(2).isApprox(VectorXd::Ones(10)));
}

TEST(TransformsUtilsTest, UnHomogenizePoints) {
  srand(7);
  Points points = Points::Random(20, 2);

  HomogeneousPoints homogenous_points = HomogenizePoints(points);
  Points recovered_points = UnHomogenizePoints(homogenous_points);

  ASSERT_TRUE(recovered_points.isApprox(points));
}

TEST(TransformsUtilsTest, TransformPoints) {
  // A square polygon for testing.
  MatrixXd points(4, 2), rotated_points(4, 2), translated_points(4, 2),
      transformed_points(4, 2);
  points << -2, 2, 2, 2, 2, -2, -2, -2;
  rotated_points << 0, 2 * sqrt(2), 2 * sqrt(2), 0, 0, -2 * sqrt(2),
      -2 * sqrt(2), 0;
  translated_points << 1, 4, 5, 4, 5, 0, 1, 0;
  transformed_points << 0, 7 + 2 * sqrt(2), 2 * sqrt(2), 7., 0, 7 - 2 * sqrt(2),
      -2 * sqrt(2), 7.;

  // Test identity transformation.
  ASSERT_TRUE(TransformPoints(points, 0., Vector2d::Zero()).isApprox(points));

  // Test rotation.
  ASSERT_TRUE(TransformPoints(points, -M_PI / 4, Vector2d::Zero())
                  .isApprox(rotated_points));
  // Invariance.
  ASSERT_TRUE(
      TransformPoints(TransformPoints(points, M_PI / 3, Vector2d::Zero()),
                      -M_PI / 3, Vector2d::Zero())
          .isApprox(points));

  // Test translation.
  ASSERT_TRUE(TransformPoints(points, 0., Vector2d{3., 2.})
                  .isApprox(translated_points));
  // Invariance.
  ASSERT_TRUE(TransformPoints(TransformPoints(points, 0., Vector2d{-8., 13.}),
                              0., Vector2d{8., -13.})
                  .isApprox(points));

  // Transformation.
  ASSERT_TRUE(TransformPoints(points, -M_PI / 4, Vector2d{0., 7.})
                  .isApprox(transformed_points));
  // Invariance.
  //ASSERT_TRUE(
  //    TransformPoints(TransformPoints(points, -M_PI / 4, Vector2d{0., 7.}),
  //                    M_PI / 4, Vector2d{0., -7.})
  //        .isApprox(points));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
