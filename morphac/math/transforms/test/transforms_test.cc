#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "math/transforms/include/transforms.h"

namespace {

using std::sqrt;

using Eigen::MatrixXd;
using Eigen::Vector2d;

using morphac::math::transforms::RotationMatrix;
using morphac::math::transforms::TransformationMatrix;

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

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
