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

using morphac::math::transforms::CanvasToWorld;
using morphac::math::transforms::RotationMatrix;
using morphac::math::transforms::TransformationMatrix;
using morphac::math::transforms::WorldToCanvas;

class TransformsTest : public ::testing::Test {
 protected:
  TransformsTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
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

TEST_F(TransformsTest, CanvasToWorld) {
  // Trivial conversion.
  ASSERT_TRUE(CanvasToWorld(Vector2i::Zero(), 1.).isApprox(Vector2d::Zero()));

  // Test conversion.
  Vector2i canvas_coord;
  Vector2d desired_world_coord;
  canvas_coord << 10, 50;
  desired_world_coord << 0.2, 1;
  ASSERT_TRUE(CanvasToWorld(canvas_coord, 0.02).isApprox(desired_world_coord));
}

TEST_F(TransformsTest, WorldToCanvas) {
  // Trivial conversion.
  ASSERT_TRUE(WorldToCanvas(Vector2d::Zero(), 1.).isApprox(Vector2i::Zero()));

  // Test conversion without bounds checking.
  Vector2d world_coord;
  Vector2i desired_canvas_coord;
  world_coord << -1., 10.;
  desired_canvas_coord << -50, 500;
  ASSERT_TRUE(WorldToCanvas(world_coord, 0.02).isApprox(desired_canvas_coord));

  // Bounds checking.
  vector<int> canvas_size = {5, 5};
  ASSERT_TRUE(WorldToCanvas(world_coord, 0.02, canvas_size)
                  .isApprox(-1 * Vector2i::Ones()));

  // More bounds.
  world_coord(0) = 2.;
  ASSERT_TRUE(WorldToCanvas(world_coord, 0.02, canvas_size)
                  .isApprox(-1 * Vector2i::Ones()));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
