#include "utils/include/geometry_utils.h"

#include "gtest/gtest.h"
#include "math/geometry/include/lines.h"
#include "utils/include/numeric_utils.h"

namespace {

using std::sqrt;
using std::tan;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::common::aliases::Point;
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
  int num_points = rectangle.rows();
  for (int i = 0; i < num_points; ++i) {
    if (!AreLinesPerpendicular(
            rectangle.row(i % num_points).transpose(),
            rectangle.row((i + 1) % num_points).transpose(),
            rectangle.row((i + 1) % num_points).transpose(),
            rectangle.row((i + 2) % num_points).transpose())) {
      return false;
    }
  }

  return true;
}

bool IsRectangleOrientedCorrectly(const Points& rectangle, const double angle) {
  int num_points = rectangle.rows();
  double slope = tan(angle);
  for (int i = 0; i < num_points; ++i) {
    auto line_spec =
        ComputeLineSpec(rectangle.row(i % num_points).transpose(),
                        rectangle.row((i + 1) % num_points).transpose());
    if (!IsEqual(line_spec.slope, slope) &&
        !IsEqual(line_spec.slope, -1. / slope)) {
      return false;
    }
  }
  return true;
}

bool IsValidArc(const Points& arc, const double radius, const Point& center,
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
                   const Point& center) {
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

bool IsValidRoundedRectangle(const Points& rounded_rectangle) {
  // Tests if the sides of the rectangle are perpendicular.
  int num_points = rounded_rectangle.rows();
  int points_per_arc = num_points / 4;

  for (int i = 0; i < 4; ++i) {
    // The lines formed by the end points of the arcs (that form the sides of
    // the rectangle) need to perpendicular.
    Point start_point1 =
        rounded_rectangle
            .row((i * points_per_arc + points_per_arc - 1) % num_points)
            .transpose();
    Point end_point1 =
        rounded_rectangle
            .row((i * points_per_arc + points_per_arc) % num_points)
            .transpose();
    Point start_point2 =
        rounded_rectangle
            .row(((i + 1) * points_per_arc + points_per_arc - 1) % num_points)
            .transpose();
    Point end_point2 =
        rounded_rectangle
            .row(((i + 1) * points_per_arc + points_per_arc) % num_points)
            .transpose();

    // Corner case when the radius is exactly half the x/y size and then we
    // get a fully rounded corner. In this case the end points of the arcs
    // repeat and we get duplicate points between which a line cannot be
    // defined.
    if (start_point1.isApprox(end_point1) &&
        start_point2.isApprox(end_point2)) {
      continue;
    }

    if (!AreLinesPerpendicular(start_point1, end_point1, start_point2,
                               end_point2)) {
      return false;
    }
  }
  return true;
}

bool IsRoundedRectangleOrientedCorrectly(const Points& rounded_rectangle,
                                         const double angle) {
  int num_points = rounded_rectangle.rows();
  int points_per_arc = num_points / 4;
  double slope = tan(angle);

  for (int i = 0; i < 4; ++i) {
    Point start_point1 =
        rounded_rectangle
            .row((i * points_per_arc + points_per_arc - 1) % num_points)
            .transpose();
    Point end_point1 =
        rounded_rectangle
            .row((i * points_per_arc + points_per_arc) % num_points)
            .transpose();
    auto line_spec = ComputeLineSpec(start_point1, end_point1);
    if (!IsEqual(line_spec.slope, slope) &&
        !IsEqual(line_spec.slope, -1. / slope)) {
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
  Points arc1_ = CreateArc(0., M_PI / 2., 1., 0.1);
  Points arc2_ = CreateArc(M_PI, M_PI / 2., 2., 0.01);
  Points arc3_ = CreateArc(-M_PI / 2, -3 * M_PI / 2., 3., 0.01, Point(-2, 3));

  Points circle1_ = CreateCircularPolygon(1., 0.01);
  Points circle2_ = CreateCircularPolygon(2., 0.01, Point(12, -9));

  Points rectangle1_ = CreateRectangularPolygon(6., 4., 0.);
  Points rectangle2_ = CreateRectangularPolygon(2., 2., 0., Point(-5., 6.));
  Points rectangle3_ = CreateRectangularPolygon(2., 2., M_PI / 4., Point(5, 4));

  Points rounded_rectangle1_ =
      CreateRoundedRectangularPolygon(6., 4., 0., 1., 0.1);
  Points rounded_rectangle2_ =
      CreateRoundedRectangularPolygon(2., 2., 0., 1., 0.1, Point(-5, 6));
  Points rounded_rectangle3_ = CreateRoundedRectangularPolygon(
      2., 2., M_PI / 4., 0.5, 0.01, Point(5, 4));
};

TEST_F(GeometryUtilsTest, CreateArc) {
  // Test the validity of each arc.
  ASSERT_TRUE(IsValidArc(arc1_, 1., Point::Zero(), M_PI / 2));
  ASSERT_TRUE(IsValidArc(arc2_, 2., Point::Zero(), M_PI / 2));
  ASSERT_TRUE(IsValidArc(arc3_, 3., Point(-2, 3), M_PI));
}

TEST_F(GeometryUtilsTest, InvalidCreateArc) {
  ASSERT_THROW(CreateArc(0., M_PI / 2., -0.1, 0.01), std::invalid_argument);
  ASSERT_THROW(CreateArc(0., M_PI / 2., 1., 0.), std::invalid_argument);
}

TEST_F(GeometryUtilsTest, CreateCircularPolygon) {
  // Test the validity of each circle.
  ASSERT_TRUE(IsValidCircle(circle1_, 1., Point::Zero()));
  ASSERT_TRUE(IsValidCircle(circle2_, 2., Point(12., -9.)));
}

TEST_F(GeometryUtilsTest, InvalidCreateCircularPolygon) {
  ASSERT_THROW(CreateCircularPolygon(-0.1, 0.01), std::invalid_argument);
  ASSERT_THROW(CreateCircularPolygon(1., 0.), std::invalid_argument);
}

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

  ASSERT_TRUE(IsRectangleOrientedCorrectly(rectangle3_, M_PI / 4));
}

TEST_F(GeometryUtilsTest, InvalidCreateRectangularPolygon) {
  ASSERT_THROW(CreateRectangularPolygon(-2., 2., 0.), std::invalid_argument);
  ASSERT_THROW(CreateRectangularPolygon(2., -2., 0.), std::invalid_argument);
}

TEST_F(GeometryUtilsTest, RoundedRectangularPolygonSize) {
  // Make sure that the rectangle sizes are correct.
  double size_x = rounded_rectangle1_.col(0).maxCoeff() -
                  rounded_rectangle1_.col(0).minCoeff();
  double size_y = rounded_rectangle1_.col(1).maxCoeff() -
                  rounded_rectangle1_.col(1).minCoeff();

  ASSERT_DOUBLE_EQ(size_x, 6.);
  ASSERT_DOUBLE_EQ(size_y, 4.);

  // Test if the rectangle is valid.
  ASSERT_TRUE(IsValidRoundedRectangle(rounded_rectangle1_));
}

TEST_F(GeometryUtilsTest, RoundedRectangularPolygonCenter) {
  // Make sure tha the rectangle center is correct.
  double size_x = rounded_rectangle2_.col(0).maxCoeff() -
                  rounded_rectangle2_.col(0).minCoeff();
  double size_y = rounded_rectangle2_.col(1).maxCoeff() -
                  rounded_rectangle2_.col(1).minCoeff();
  double center_x = rounded_rectangle2_.col(0).minCoeff() + size_x / 2;
  double center_y = rounded_rectangle2_.col(1).minCoeff() + size_y / 2;

  ASSERT_DOUBLE_EQ(center_x, -5.);
  ASSERT_DOUBLE_EQ(center_y, 6.);

  // Test if the rectangle is valid.
  ASSERT_TRUE(IsValidRoundedRectangle(rounded_rectangle2_));
}

TEST_F(GeometryUtilsTest, RoundedRectangularPolygonRotation) {
  // Test center. As the rectangle is oriented, max - min does not give the
  // size, but the value can still be used to compute the center.
  double diff_x = rounded_rectangle3_.col(0).maxCoeff() -
                  rounded_rectangle3_.col(0).minCoeff();
  double diff_y = rounded_rectangle3_.col(1).maxCoeff() -
                  rounded_rectangle3_.col(1).minCoeff();
  double center_x = rounded_rectangle3_.col(0).minCoeff() + diff_x / 2;
  double center_y = rounded_rectangle3_.col(1).minCoeff() + diff_y / 2;

  ASSERT_DOUBLE_EQ(center_x, 5.);
  ASSERT_DOUBLE_EQ(center_y, 4.);

  ASSERT_TRUE(
      IsRoundedRectangleOrientedCorrectly(rounded_rectangle3_, M_PI / 4));
}

TEST_F(GeometryUtilsTest, InvalidRoundedRectangularPolygon) {
  // If the radius is more than half the sizes, it is invalid.
  ASSERT_THROW(
      CreateRoundedRectangularPolygon(6., 4., 0., 3., 0.1, Point::Zero()),
      std::invalid_argument);
  ASSERT_THROW(
      CreateRoundedRectangularPolygon(6., 4., 0., 2.1, 0.1, Point::Zero()),
      std::invalid_argument);
}

TEST_F(GeometryUtilsTest, InvalidCreateRoundedRectangularPolygon) {
  ASSERT_THROW(CreateRoundedRectangularPolygon(-2., 2., 0., 1., 0.1),
               std::invalid_argument);
  ASSERT_THROW(CreateRoundedRectangularPolygon(2., -2., 0., 1., 0.1),
               std::invalid_argument);
  ASSERT_THROW(CreateRoundedRectangularPolygon(2., 2., 0., -0.1, 0.1),
               std::invalid_argument);
  ASSERT_THROW(CreateRoundedRectangularPolygon(2., 2., 0., 1., 0.),
               std::invalid_argument);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
