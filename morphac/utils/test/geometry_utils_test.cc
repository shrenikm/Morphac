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
using morphac::math::geometry::ComputeLineSpec;
using morphac::utils::CreateArc;
using morphac::utils::CreateCircularPolygon;
using morphac::utils::CreateRectangularPolygon;
using morphac::utils::CreateRoundedRectangularPolygon;
using morphac::utils::IsEqual;

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

bool IsValidArc(const Points& arc, const double radius, const Vector2d& center,
                const double angular_spread) {
  // Test if each point is the same distance from the center.
  for (int i = 0; i < arc.rows(); ++i) {
    if (!IsEqual((arc.row(i).transpose() - center).norm(), radius)) {
      return false;
    }
  }

  // Test the arc length.
  double arc_length = 0;
  for (int i = 0; i < arc.rows() - 1; ++i) {
    arc_length += (arc.row(i) - arc.row(i + 1)).norm();
  }

  if (!IsEqual(arc_length, radius * angular_spread, 1e-3)) {
    return false;
  }

  return true;
}

bool IsValidCircle(const Points& circle, const double radius,
                   const Vector2d& center) {
  // Test if each point is the same distance from the center.
  for (int i = 0; i < circle.rows(); ++i) {
    if (!IsEqual((circle.row(i).transpose() - center).norm(), radius)) {
      return false;
    }
  }

  // Test the circumference.
  double circumference = 0;
  for (int i = 0; i < circle.rows() - 1; ++i) {
    circumference += (circle.row(i) - circle.row(i + 1)).norm();
  }

  if (!IsEqual(circumference, 2 * M_PI * radius, 1e-1)) {
    return false;
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
  Points arc1_ = CreateArc(0., M_PI / 2., 1., 0.1, Vector2d::Zero());
  Points arc2_ = CreateArc(M_PI, M_PI / 2., 2., 0.01, Vector2d::Zero());
  Points arc3_ =
      CreateArc(-M_PI / 2, -3 * M_PI / 2., 3., 0.01, Vector2d(-2, 3));
  Points circle1_ = CreateCircularPolygon(1., 0.01, Vector2d::Zero());
  Points circle2_ = CreateCircularPolygon(2., 0.01, Vector2d(12, -9));
};

TEST_F(GeometryUtilsTest, RectangularPolygonSize) {
  // Make sure that the rectangle sizes are correct.
  double size_x = rectangle1_.col(0).maxCoeff() - rectangle1_.col(0).minCoeff();
  double size_y = rectangle1_.col(1).maxCoeff() - rectangle1_.col(1).minCoeff();

  ASSERT_DOUBLE_EQ(size_x, 6.);
  ASSERT_DOUBLE_EQ(size_y, 4.);

  // Test if the rectangle is valid.
  ASSERT_TRUE(IsValidRectangle(rectangle1_));
}

TEST_F(GeometryUtilsTest, RectangularPolygonCenter) {
  // Make sure tha the rectangle center is correct.
  double size_x = rectangle2_.col(0).maxCoeff() - rectangle2_.col(0).minCoeff();
  double size_y = rectangle2_.col(1).maxCoeff() - rectangle2_.col(1).minCoeff();
  double center_x = rectangle2_.col(0).minCoeff() + size_x / 2;
  double center_y = rectangle2_.col(1).minCoeff() + size_y / 2;

  ASSERT_DOUBLE_EQ(center_x, -5.);
  ASSERT_DOUBLE_EQ(center_y, 6.);

  // Test if the rectangle is valid.
  ASSERT_TRUE(IsValidRectangle(rectangle2_));
}

TEST_F(GeometryUtilsTest, RectangularPolygonRotation) {
  // Test center. As the rectangle is oriented, max - min does not give the
  // size, but the value can still be used to compute the center.
  double diff_x = rectangle3_.col(0).maxCoeff() - rectangle3_.col(0).minCoeff();
  double diff_y = rectangle3_.col(1).maxCoeff() - rectangle3_.col(1).minCoeff();
  double center_x = rectangle3_.col(0).minCoeff() + diff_x / 2;
  double center_y = rectangle3_.col(1).minCoeff() + diff_y / 2;

  ASSERT_DOUBLE_EQ(center_x, 5.);
  ASSERT_DOUBLE_EQ(center_y, 4.);

  // Test if the orientation is correct.
  int rows = rectangle3_.rows();
  for (int i = 0; i < rows; ++i) {
    auto line_spec =
        ComputeLineSpec(rectangle3_.row(i % rows).transpose(),
                        rectangle3_.row((i + 1) % rows).transpose());
    ASSERT_TRUE(IsEqual(line_spec.slope, 1.) || IsEqual(line_spec.slope, -1.));
  }

  // Test if the rectangle is valid.
  ASSERT_TRUE(IsValidRectangle(rectangle3_));
}

TEST_F(GeometryUtilsTest, CreateArc) {
  // Test the validity of each arc.
  ASSERT_TRUE(IsValidArc(arc1_, 1., Vector2d::Zero(), M_PI / 2));
  ASSERT_TRUE(IsValidArc(arc2_, 2., Vector2d::Zero(), M_PI / 2));
  ASSERT_TRUE(IsValidArc(arc3_, 3., Vector2d(-2, 3), M_PI));
}

TEST_F(GeometryUtilsTest, CreateCircularPolygon) {
  // Test the validity of each circle.
  ASSERT_TRUE(IsValidCircle(circle1_, 1., Vector2d::Zero()));
  ASSERT_TRUE(IsValidCircle(circle2_, 2., Vector2d(12., -9.)));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

