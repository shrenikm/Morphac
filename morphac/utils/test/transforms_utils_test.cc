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
using morphac::utils::TranslatePoints;
using morphac::utils::UnHomogenizePoints;

class TransformsUtilsTest : public ::testing::Test {
 protected:
  TransformsUtilsTest() {
    // Set random seed for Eigen.
    srand(7);

    cube_.resize(4, 2);
    cube_ << -2, 2, 2, 2, 2, -2, -2, -2;
    points_ = Points::Random(10, 2);
  }

  void SetUp() override {}

  Points cube_, points_;
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

TEST_F(TransformsUtilsTest, TranslatePoints) {
  Vector2d translation = Vector2d::Random();

  // Zero translation.
  ASSERT_TRUE(TranslatePoints(points_, Vector2d::Zero()).isApprox(points_));

  Points translated_points = TranslatePoints(points_, translation);
  for (int i = 0; i < translated_points.rows(); ++i) {
    ASSERT_DOUBLE_EQ(translated_points(i, 0), points_(i, 0) + translation(0));
    ASSERT_DOUBLE_EQ(translated_points(i, 1), points_(i, 1) + translation(1));
  }
}

TEST_F(TransformsUtilsTest, RotatePoints) {
  Points rotated_cube1(4, 2), rotated_cube2(4, 2);

  // Testing the default rotation without providing a center.
  rotated_cube1 << 0, 2 * sqrt(2), 2 * sqrt(2), 0, 0, -2 * sqrt(2),
      -2 * sqrt(2), 0;

  ASSERT_TRUE(RotatePoints(cube_, -M_PI / 4).isApprox(rotated_cube1));

  // Testing rotation about a center.
  rotated_cube2 << -2 - 2 * sqrt(2), -2 + 2 * sqrt(2), -2, -2 + 4 * sqrt(2),
      -2 + 2 * sqrt(2), -2 + 2 * sqrt(2), -2, -2;

  std::cout << RotatePoints(cube_, M_PI / 4, Vector2d{-2, -2}) << std::endl;

  ASSERT_TRUE(
      RotatePoints(cube_, M_PI / 4, Vector2d{-2, -2}).isApprox(rotated_cube2));
}

TEST_F(TransformsUtilsTest, TransformPoints) {
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
  // ASSERT_TRUE(
  //    TransformPoints(TransformPoints(points, -M_PI / 4, Vector2d{0., 7.}),
  //                    M_PI / 4, Vector2d{0., -7.})
  //        .isApprox(points));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
