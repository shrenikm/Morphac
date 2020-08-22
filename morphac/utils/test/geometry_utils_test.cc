#include "gtest/gtest.h"

#include "math/geometry/include/lines.h"
#include "utils/include/geometry_utils.h"
#include "utils/include/numeric_utils.h"

namespace {

using std::sqrt;

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::VectorXd;

using morphac::common::aliases::Points;
using morphac::math::geometry::AreLinesPerpendicular;
using morphac::utils::CreateArc;
using morphac::utils::CreateCircularPolygon;
using morphac::utils::CreateRectangularPolygon;
using morphac::utils::CreateRoundedRectangularPolygon;
using morphac::utils::IsEqual;

// bool IsValidRectangle(const Points& rectangle, const double expected_size_x,
//                      const double expected_size_y,
//                      const Vector2d& expected_center) {
//  // Test that the size is correct.
//  double size_x = rectangle.col(0).maxCoeff() - rectangle.col(0).minCoeff();
//  double size_y = rectangle.col(1).maxCoeff() - rectangle.col(1).minCoeff();
//
//  if (!IsEqual(size_x, expected_size_x)) {
//    return false;
//  }
//
//  if (!IsEqual(size_y, expected_size_y)) {
//    return false;
//  }
//
//  // Test the center.
//  double center_x = rectangle.col(0).minCoeff() + size_x / 2;
//  double center_y = rectangle.col(1).minCoeff() + size_y / 2;
//}

bool IsValidRectangle(const Points& rectangle) {
  // Tests if the sides of the rectangle are perpendicular.
  int rows = rectangle.rows();
  for (int i = 0; i < rows; ++i) {
    if (!AreLinesPerpendicular(rectangle.row(i % rows).transpose(),
                               rectangle.row((i + 1) % rows).transpose(),
                               rectangle.row((i + 1) % rows).transpose(),
                               rectangle.row((i + 2) % rows).transpose())) {
      return false;
    }
  }

  return true;
}

class GeometryUtilsTest : public ::testing::Test {
 protected:
  GeometryUtilsTest() {
    // Set random seed for Eigen.
    srand(7);
  }
  void SetUp() override {}
  Points rectangle1_ = CreateRectangularPolygon(6., 4., 0., Vector2d::Zero());
  Points rectangle2_ = CreateRectangularPolygon(2., 2., 0., Vector2d(-5., 6.));
  Points rectangle3_ =
      CreateRectangularPolygon(2., 2., M_PI / 4., Vector2d(5, 4));
};

TEST_F(GeometryUtilsTest, RectangularPolygonSize) {
  // Make sure that the rectangle sizes are correct.
  double size_x = rectangle1_.col(0).maxCoeff() - rectangle1_.col(0).minCoeff();
  double size_y = rectangle1_.col(1).maxCoeff() - rectangle1_.col(1).minCoeff();

  ASSERT_DOUBLE_EQ(size_x, 6.);
  ASSERT_DOUBLE_EQ(size_y, 4.);
  ASSERT_TRUE(IsValidRectangle(rectangle1_));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

