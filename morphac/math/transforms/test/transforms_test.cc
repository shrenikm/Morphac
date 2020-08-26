#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "math/transforms/include/transforms.h"

namespace {

using std::sqrt;
using std::vector;

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::Vector2i;
using Eigen::VectorXd;

using morphac::common::aliases::HomogeneousPoints;
using morphac::common::aliases::Pixels;
using morphac::common::aliases::Points;
using morphac::math::transforms::CanvasToWorld;
using morphac::math::transforms::RotationMatrix;
using morphac::math::transforms::RotatePoints;
using morphac::math::transforms::TransformationMatrix;
using morphac::math::transforms::TransformPoints;
using morphac::math::transforms::TranslatePoints;
using morphac::math::transforms::WorldToCanvas;

class TransformsTest : public ::testing::Test {
 protected:
  TransformsTest() {
    // Set random seed for Eigen.
    srand(7);

    cube_.resize(4, 2);
    cube_ << -2, 2, 2, 2, 2, -2, -2, -2;
    points_ = Points::Random(10, 2);
  }

  void SetUp() override {}

  Points cube_, points_;
};

TEST_F(TransformsTest, RotationMatrixProperties) {
  // Tests the properties of the rotation matrix.
  // Test trivial zero rotation.
  MatrixXd rot = RotationMatrix(0.);

  // Obvious but ensures structured testing.
  ASSERT_EQ(rot.rows(), 2);
  ASSERT_EQ(rot.cols(), 2);

  ASSERT_TRUE(rot.isApprox(MatrixXd::Identity(2, 2)));

  // Rotation matrix need to be orthogonal, for any angle.
  rot = RotationMatrix(0.7);
  ASSERT_TRUE((rot * rot.transpose()).isApprox(MatrixXd::Identity(2, 2)));
  ASSERT_TRUE((rot.transpose() * rot).isApprox(MatrixXd::Identity(2, 2)));
}

TEST_F(TransformsTest, RotationMatrixFunctionality) {
  // Tests that the rotation matrix can be used to perform rotations.

  // Matrix that rotates by 45 degrees.
  MatrixXd rot = RotationMatrix(M_PI / 4);

  // Point to rotate.
  Vector2d point(2), desired_point(2);
  point << 2., 0.;
  desired_point << sqrt(2), sqrt(2);

  Vector2d rotated_point = rot * point;

  ASSERT_TRUE(rotated_point.isApprox(desired_point));

  // Test the same for a negative angle.
  rot = RotationMatrix(-M_PI / 4);
  desired_point(1) = -sqrt(2);

  rotated_point = rot * point;

  ASSERT_TRUE(rotated_point.isApprox(desired_point));

  // Test the equivalence of positive and negative angles.
  double angle = 0.7;
  ASSERT_TRUE(
      RotationMatrix(angle).isApprox(RotationMatrix(-(2 * M_PI - angle))));
  angle = 2.5;
  ASSERT_TRUE(
      RotationMatrix(angle).isApprox(RotationMatrix(-(2 * M_PI - angle))));
}

TEST_F(TransformsTest, TransformationMatrixProperties) {
  // Tests the properties of the transformation matrix.
  // Test trivial zero rotation and translation.
  MatrixXd tf = TransformationMatrix(0., Vector2d::Zero());

  // Obvious but ensures structured testing.
  ASSERT_EQ(tf.rows(), 3);
  ASSERT_EQ(tf.cols(), 3);

  ASSERT_TRUE(tf.isApprox(MatrixXd::Identity(3, 3)));

  // Transformation matrix need to be orthogonal, for any angle and zero
  // translation.
  tf = TransformationMatrix(0.7, Vector2d::Zero());
  ASSERT_TRUE((tf * tf.transpose()).isApprox(MatrixXd::Identity(3, 3)));
  ASSERT_TRUE((tf.transpose() * tf).isApprox(MatrixXd::Identity(3, 3)));
}

TEST_F(TransformsTest, TransformationMatrixFunctionality) {
  // Tests that the transformation matrix can be used to perform rotations and
  // translations.

  // Matrix that rotates by 45 degrees and doesn't translate.
  MatrixXd tf = TransformationMatrix(M_PI / 4, Vector2d::Zero());

  // Point to rotate. (Homogeneous coordinates in 3d).
  VectorXd point(3), desired_point(3);
  point << 2., 0., 1;
  desired_point << sqrt(2), sqrt(2), 1;

  VectorXd transformed_point = tf * point;

  ASSERT_TRUE(transformed_point.isApprox(desired_point));

  // Test the same for a negative angle and non zero translation.
  Vector2d translation;
  translation << 0., 5.;
  tf = TransformationMatrix(-M_PI / 4, translation);
  desired_point(1) = -sqrt(2) + 5.;

  transformed_point = tf * point;

  ASSERT_TRUE(transformed_point.isApprox(desired_point));
}

TEST_F(TransformsTest, TranslatePoints) {
  Vector2d translation = Vector2d::Random();

  // Zero translation.
  ASSERT_TRUE(TranslatePoints(points_, Vector2d::Zero()).isApprox(points_));

  Points translated_points = TranslatePoints(points_, translation);
  for (int i = 0; i < translated_points.rows(); ++i) {
    ASSERT_DOUBLE_EQ(translated_points(i, 0), points_(i, 0) + translation(0));
    ASSERT_DOUBLE_EQ(translated_points(i, 1), points_(i, 1) + translation(1));
  }
}

TEST_F(TransformsTest, RotatePoints) {
  Points rotated_cube1(4, 2), rotated_cube2(4, 2);

  // Testing the default rotation without providing a center.
  rotated_cube1 << 0, 2 * sqrt(2), 2 * sqrt(2), 0, 0, -2 * sqrt(2),
      -2 * sqrt(2), 0;

  ASSERT_TRUE(RotatePoints(cube_, -M_PI / 4).isApprox(rotated_cube1));

  // Testing rotation about a center.
  rotated_cube2 << -2 - 2 * sqrt(2), -2 + 2 * sqrt(2), -2, -2 + 4 * sqrt(2),
      -2 + 2 * sqrt(2), -2 + 2 * sqrt(2), -2, -2;

  ASSERT_TRUE(
      RotatePoints(cube_, M_PI / 4, Vector2d{-2, -2}).isApprox(rotated_cube2));
}

TEST_F(TransformsTest, TransformPoints) {
  // A square polygon for testing.
  MatrixXd rotated_points(4, 2), translated_points(4, 2),
      transformed_points(4, 2);
  rotated_points << 0, 2 * sqrt(2), 2 * sqrt(2), 0, 0, -2 * sqrt(2),
      -2 * sqrt(2), 0;
  translated_points << 1, 4, 5, 4, 5, 0, 1, 0;
  transformed_points << 0, 7 + 2 * sqrt(2), 2 * sqrt(2), 7., 0, 7 - 2 * sqrt(2),
      -2 * sqrt(2), 7.;

  // Test identity transformation.
  ASSERT_TRUE(TransformPoints(cube_, 0., Vector2d::Zero()).isApprox(cube_));

  // Test rotation.
  ASSERT_TRUE(TransformPoints(cube_, -M_PI / 4, Vector2d::Zero())
                  .isApprox(rotated_points));
  // Invariance.
  ASSERT_TRUE(
      TransformPoints(TransformPoints(cube_, M_PI / 3, Vector2d::Zero()),
                      -M_PI / 3, Vector2d::Zero())
          .isApprox(cube_));

  // Test translation.
  ASSERT_TRUE(
      TransformPoints(cube_, 0., Vector2d{3., 2.}).isApprox(translated_points));
  // Invariance.
  ASSERT_TRUE(TransformPoints(TransformPoints(cube_, 0., Vector2d{-8., 13.}),
                              0., Vector2d{8., -13.})
                  .isApprox(cube_));

  // Transformation.
  ASSERT_TRUE(TransformPoints(cube_, -M_PI / 4, Vector2d{0., 7.})
                  .isApprox(transformed_points));
  // Invariance.
  ASSERT_TRUE(TransformPoints(TransformPoints(TransformPoints(cube_, -M_PI / 4,
                                                              Vector2d{0., 7.}),
                                              0., Vector2d{0., -7.}),
                              M_PI / 4, Vector2d::Zero())
                  .isApprox(cube_));
}

TEST_F(TransformsTest, CanvasToWorld) {
  // Trivial conversion.
  // Note that we cannot construct the zero vector inplace as the function
  // overloading becomes ambiguous.
  Vector2i zero_coord = Vector2i::Zero();
  ASSERT_TRUE(CanvasToWorld(zero_coord, 0.1).isApprox(Vector2d::Zero()));

  // Test conversion.
  Vector2i canvas_coord;
  Vector2d desired_world_coord;
  canvas_coord << 10, 50;
  desired_world_coord << 0.2, 1;
  ASSERT_TRUE(CanvasToWorld(canvas_coord, 0.02).isApprox(desired_world_coord));
}

TEST_F(TransformsTest, CanvasToWorldMultiplePoints) {
  // Trivial conversion.
  // Note that we cannot construct the zero points inplace as the function
  // overloading becomes ambiguous.
  Pixels zero_coords = Pixels::Zero(10, 2);
  ASSERT_TRUE(CanvasToWorld(zero_coords, 0.1).isApprox(Points::Zero(10, 2)));

  Pixels canvas_coords(3, 2);
  Points desired_world_coords(3, 2);
  canvas_coords << 2, 3, 20, 30, -40, -75;
  desired_world_coords << 0.2, 0.3, 2, 3, -4, -7.5;
  ASSERT_TRUE(CanvasToWorld(canvas_coords, 0.1).isApprox(desired_world_coords));
}

TEST_F(TransformsTest, WorldToCanvas) {
  // Trivial conversion.
  // Note that we cannot construct the zero vector inplace as the function
  // overloading becomes ambiguous.
  Vector2d zero_coord = Vector2d::Zero();
  ASSERT_TRUE(WorldToCanvas(zero_coord, 0.1).isApprox(Vector2i::Zero()));

  // Test conversion without bounds checking.
  Vector2d world_coord;
  Vector2i desired_canvas_coord;
  world_coord << -1., 10.;
  desired_canvas_coord << -50, 500;
  ASSERT_TRUE(WorldToCanvas(world_coord, 0.02).isApprox(desired_canvas_coord));

  // Bounds checking.
  vector<int> canvas_size = {100, 100};
  ASSERT_TRUE(WorldToCanvas(Vector2d(-1., 1.), 0.02, canvas_size)
                  .isApprox(-1 * Vector2i::Ones()));
  ASSERT_TRUE(WorldToCanvas(Vector2d(1., -1.), 0.02, canvas_size)
                  .isApprox(-1 * Vector2i::Ones()));
  ASSERT_TRUE(WorldToCanvas(Vector2d(5., 1.), 0.02, canvas_size)
                  .isApprox(-1 * Vector2i::Ones()));
  ASSERT_TRUE(WorldToCanvas(Vector2d(1., 5.), 0.02, canvas_size)
                  .isApprox(-1 * Vector2i::Ones()));
  ASSERT_FALSE(WorldToCanvas(Vector2d(1., 1.), 0.02, canvas_size)
                   .isApprox(-1 * Vector2i::Ones()));
}

TEST_F(TransformsTest, WorldToCanvasRounding) {
  // Test if while converting from world to canvas, we round the vector
  // correctly.
  Vector2d world_coord;
  Vector2i desired_canvas_coord;

  world_coord << 2.225, 3.775;
  desired_canvas_coord << 22, 38;

  ASSERT_TRUE(WorldToCanvas(world_coord, 0.1).isApprox(desired_canvas_coord));
}

TEST_F(TransformsTest, WorldToCanvasMultiplePoints) {
  // Trivial conversion.
  // Note that we cannot construct the zero points inplace as the function
  // overloading becomes ambiguous.
  Points zero_coords = Points::Zero(10, 2);
  ASSERT_TRUE(WorldToCanvas(zero_coords, 0.1).isApprox(Pixels::Zero(10, 2)));

  Points world_coords(5, 2);
  Pixels desired_canvas_coords(5, 2);
  world_coords << -1., 10., 10., -1., 20., 7., 1., 40., 5., 6.;
  desired_canvas_coords << -10, 100, 100, -10, 200, 70, 10, 400, 50, 60;
  ASSERT_TRUE(WorldToCanvas(world_coords, 0.1).isApprox(desired_canvas_coords));

  // Bounds checking.
  vector<int> canvas_size = {100, 100};
  Pixels canvas_coords = WorldToCanvas(world_coords, 0.1, canvas_size);

  // The first two points must be outside the canvas.
  ASSERT_TRUE(canvas_coords.row(0).isApprox(-1 * Vector2i::Ones().transpose()));
  ASSERT_TRUE(canvas_coords.row(1).isApprox(-1 * Vector2i::Ones().transpose()));
  ASSERT_TRUE(canvas_coords.row(2).isApprox(-1 * Vector2i::Ones().transpose()));
  ASSERT_TRUE(canvas_coords.row(3).isApprox(-1 * Vector2i::Ones().transpose()));
  ASSERT_FALSE(
      canvas_coords.row(4).isApprox(-1 * Vector2i::Ones().transpose()));
}

TEST_F(TransformsTest, WorldToCanvasRoundingMultiplePoints) {
  Points world_coords(2, 2);
  Pixels desired_canvas_coords(2, 2);

  world_coords << 1.712, -1.291, 3.445, 3.455;
  desired_canvas_coords << 17, -13, 34, 35;

  ASSERT_TRUE(WorldToCanvas(world_coords, 0.1).isApprox(desired_canvas_coords));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
