#include "math/transforms/include/transforms.h"

#include "Eigen/Dense"
#include "gtest/gtest.h"

namespace {

using std::sqrt;
using std::vector;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::common::aliases::HomogeneousPoints;
using morphac::common::aliases::Pixel;
using morphac::common::aliases::Pixels;
using morphac::common::aliases::Point;
using morphac::common::aliases::Points;
using morphac::math::transforms::CanvasToWorld;
using morphac::math::transforms::RotatePoints;
using morphac::math::transforms::RotationMatrix;
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
  Point point(2), desired_point(2);
  point << 2., 0.;
  desired_point << sqrt(2), sqrt(2);

  Point rotated_point = rot * point;

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
  MatrixXd tf = TransformationMatrix(0., Point::Zero());

  // Obvious but ensures structured testing.
  ASSERT_EQ(tf.rows(), 3);
  ASSERT_EQ(tf.cols(), 3);

  ASSERT_TRUE(tf.isApprox(MatrixXd::Identity(3, 3)));

  // Transformation matrix need to be orthogonal, for any angle and zero
  // translation.
  tf = TransformationMatrix(0.7, Point::Zero());
  ASSERT_TRUE((tf * tf.transpose()).isApprox(MatrixXd::Identity(3, 3)));
  ASSERT_TRUE((tf.transpose() * tf).isApprox(MatrixXd::Identity(3, 3)));
}

TEST_F(TransformsTest, TransformationMatrixFunctionality) {
  // Tests that the transformation matrix can be used to perform rotations and
  // translations.

  // Matrix that rotates by 45 degrees and doesn't translate.
  MatrixXd tf = TransformationMatrix(M_PI / 4, Point::Zero());

  // Point to rotate. (Homogeneous coordinates in 3d).
  VectorXd point(3), desired_point(3);
  point << 2., 0., 1;
  desired_point << sqrt(2), sqrt(2), 1;

  VectorXd transformed_point = tf * point;

  ASSERT_TRUE(transformed_point.isApprox(desired_point));

  // Test the same for a negative angle and non zero translation.
  Point translation;
  translation << 0., 5.;
  tf = TransformationMatrix(-M_PI / 4, translation);
  desired_point(1) = -sqrt(2) + 5.;

  transformed_point = tf * point;

  ASSERT_TRUE(transformed_point.isApprox(desired_point));
}

TEST_F(TransformsTest, TranslatePoints) {
  Point translation = Point::Random();

  // Zero translation.
  ASSERT_TRUE(TranslatePoints(points_, Point::Zero()).isApprox(points_));

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
      RotatePoints(cube_, M_PI / 4, Point{-2, -2}).isApprox(rotated_cube2));
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
  ASSERT_TRUE(TransformPoints(cube_, 0., Point::Zero()).isApprox(cube_));

  // Test rotation.
  ASSERT_TRUE(TransformPoints(cube_, -M_PI / 4, Point::Zero())
                  .isApprox(rotated_points));
  // Invariance.
  ASSERT_TRUE(TransformPoints(TransformPoints(cube_, M_PI / 3, Point::Zero()),
                              -M_PI / 3, Point::Zero())
                  .isApprox(cube_));

  // Test translation.
  ASSERT_TRUE(
      TransformPoints(cube_, 0., Point{3., 2.}).isApprox(translated_points));
  // Invariance.
  ASSERT_TRUE(TransformPoints(TransformPoints(cube_, 0., Point{-8., 13.}), 0.,
                              Point{8., -13.})
                  .isApprox(cube_));

  // Transformation.
  ASSERT_TRUE(TransformPoints(cube_, -M_PI / 4, Point{0., 7.})
                  .isApprox(transformed_points));
  // Invariance.
  ASSERT_TRUE(TransformPoints(TransformPoints(TransformPoints(cube_, -M_PI / 4,
                                                              Point{0., 7.}),
                                              0., Point{0., -7.}),
                              M_PI / 4, Point::Zero())
                  .isApprox(cube_));
}

TEST_F(TransformsTest, CanvasToWorld) {
  // Trivial conversion between the origins of the canvas and world.
  // Note that we cannot construct the zero vector inplace as the function
  // overloading becomes ambiguous.
  vector<int> canvas_size = {100, 200};
  Pixel zero_coord1 = Pixel::Zero(2);
  Pixel zero_coord2(100, 0);
  ASSERT_TRUE(
      CanvasToWorld(zero_coord1, 0.1, canvas_size).isApprox(Point(0., 10.)));
  ASSERT_TRUE(
      CanvasToWorld(zero_coord2, 0.1, canvas_size).isApprox(Point::Zero()));

  // Test conversion.
  Pixel canvas_coord;
  Point desired_world_coord;
  canvas_coord << 10, 50;
  desired_world_coord << 1., 1.8;
  ASSERT_TRUE(CanvasToWorld(canvas_coord, 0.02, canvas_size)
                  .isApprox(desired_world_coord));
}

TEST_F(TransformsTest, CanvasToWorldMultiplePoints) {
  // Trivial conversion.
  // Note that we cannot construct the zero points inplace as the function
  // overloading becomes ambiguous.
  vector<int> canvas_size = {50, 100};
  Pixels zero_coords1 = Pixels::Zero(3, 2);
  Pixels zero_coords2(3, 2);
  zero_coords2 << 50, 0, 50, 0, 50, 0;
  Points world_zero_coords1(3, 2);
  world_zero_coords1 << 0., 5., 0., 5., 0., 5.;
  ASSERT_TRUE(CanvasToWorld(zero_coords1, 0.1, canvas_size)
                  .isApprox(world_zero_coords1));
  ASSERT_TRUE(CanvasToWorld(zero_coords2, 0.1, canvas_size)
                  .isApprox(Points::Zero(3, 2)));

  Pixels canvas_coords(3, 2);
  Points desired_world_coords(3, 2);
  canvas_coords << 2, 3, 20, 30, 40, 75;
  desired_world_coords << 0.3, 4.8, 3, 3, 7.5, 1.;
  ASSERT_TRUE(CanvasToWorld(canvas_coords, 0.1, canvas_size)
                  .isApprox(desired_world_coords));
}

TEST_F(TransformsTest, WorldToCanvas) {
  // Trivial conversion.
  // Note that we cannot construct the zero vector inplace as the function
  // overloading becomes ambiguous.
  vector<int> canvas_size = {100, 200};
  Point zero_coord1 = Point::Zero();
  Point zero_coord2(0., 10);
  ASSERT_TRUE(
      WorldToCanvas(zero_coord1, 0.1, canvas_size).isApprox(Pixel(100, 0)));
  ASSERT_TRUE(
      WorldToCanvas(zero_coord2, 0.1, canvas_size).isApprox(Pixel::Zero()));

  Point world_coord;
  Pixel desired_canvas_coord;
  world_coord << 1., 1.8;
  desired_canvas_coord << 10, 50;
  ASSERT_TRUE(WorldToCanvas(world_coord, 0.02, canvas_size)
                  .isApprox(desired_canvas_coord));

  // TODO: Enable this if bounds checking is enabled.
  //// Bounds checking.
  // vector<int> canvas_size = {100, 100};
  // ASSERT_TRUE(WorldToCanvas(Point(-1., 1.), 0.02, canvas_size)
  //                .isApprox(-1 * Pixel::Ones()));
  // ASSERT_TRUE(WorldToCanvas(Point(1., -1.), 0.02, canvas_size)
  //                .isApprox(-1 * Pixel::Ones()));
  // ASSERT_TRUE(WorldToCanvas(Point(5., 1.), 0.02, canvas_size)
  //                .isApprox(-1 * Pixel::Ones()));
  // ASSERT_TRUE(WorldToCanvas(Point(1., 5.), 0.02, canvas_size)
  //                .isApprox(-1 * Pixel::Ones()));
  // ASSERT_FALSE(WorldToCanvas(Point(1., 1.), 0.02, canvas_size)
  //                 .isApprox(-1 * Pixel::Ones()));
}

TEST_F(TransformsTest, WorldToCanvasRounding) {
  // Test if while converting from world to canvas, we round the vector
  // correctly.
  vector<int> canvas_size = {100, 100};
  Point world_coord;
  Pixel desired_canvas_coord;

  world_coord << 2.225, 6.225;
  desired_canvas_coord << 38, 22;

  ASSERT_TRUE(WorldToCanvas(world_coord, 0.1, canvas_size)
                  .isApprox(desired_canvas_coord));
}

TEST_F(TransformsTest, WorldToCanvasMultiplePoints) {
  // Trivial conversion.
  // Note that we cannot construct the zero points inplace as the function
  // overloading becomes ambiguous.
  vector<int> canvas_size = {50, 100};
  Points zero_coords1 = Points::Zero(3, 2);
  Points zero_coords2(3, 2);
  zero_coords2 << 0., 5., 0., 5., 0., 5.;
  Pixels canvas_zero_coords1(3, 2);
  canvas_zero_coords1 << 50, 0, 50, 0, 50, 0;
  ASSERT_TRUE(WorldToCanvas(zero_coords1, 0.1, canvas_size)
                  .isApprox(canvas_zero_coords1));
  ASSERT_TRUE(WorldToCanvas(zero_coords2, 0.1, canvas_size)
                  .isApprox(Pixels::Zero(3, 2)));

  Points world_coords(3, 2);
  Pixels desired_canvas_coords(3, 2);
  world_coords << 0.3, 4.8, 3, 3, 7.5, 1.;
  desired_canvas_coords << 2, 3, 20, 30, 40, 75;
  ASSERT_TRUE(WorldToCanvas(world_coords, 0.1, canvas_size)
                  .isApprox(desired_canvas_coords));

  // TODO: Enable this if bounds checking is enabled.
  //// Bounds checking.
  // vector<int> canvas_size = {100, 100};
  // Pixels canvas_coords = WorldToCanvas(world_coords, 0.1, canvas_size);

  //// The first two points must be outside the canvas.
  // ASSERT_TRUE(canvas_coords.row(0).isApprox(-1 *
  // Pixel::Ones().transpose()));
  // ASSERT_TRUE(canvas_coords.row(1).isApprox(-1 *
  // Pixel::Ones().transpose()));
  // ASSERT_TRUE(canvas_coords.row(2).isApprox(-1 *
  // Pixel::Ones().transpose()));
  // ASSERT_TRUE(canvas_coords.row(3).isApprox(-1 *
  // Pixel::Ones().transpose()));
  // ASSERT_FALSE(
  //    canvas_coords.row(4).isApprox(-1 * Pixel::Ones().transpose()));
}

TEST_F(TransformsTest, WorldToCanvasRoundingMultiplePoints) {
  vector<int> canvas_size = {100, 100};
  Points world_coords(2, 2);
  Pixels desired_canvas_coords(2, 2);

  world_coords << 1.712, 8.709, 3.445, 6.545;
  desired_canvas_coords << 13, 17, 35, 34;

  ASSERT_TRUE(WorldToCanvas(world_coords, 0.1, canvas_size)
                  .isApprox(desired_canvas_coords));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
