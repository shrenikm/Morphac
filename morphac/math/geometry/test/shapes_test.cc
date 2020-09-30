#include "math/geometry/include/shapes.h"

#include "gtest/gtest.h"

namespace {

using Eigen::Vector2d;

using morphac::common::aliases::Point;
using morphac::math::geometry::ArcShape;
using morphac::math::geometry::CircleShape;
using morphac::math::geometry::RectangleShape;
using morphac::math::geometry::RoundedRectangleShape;
using morphac::math::geometry::TriangleShape;
using morphac::utils::IsEqual;

class ShapesTest : public ::testing::Test {
 protected:
  ShapesTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}

  // Standard shapes
  ArcShape arc_shape_{Point(-1., 2.), M_PI / 4, M_PI, 2.};
  CircleShape circle_shape_{Point(-1., 2.), 2.};
  RectangleShape rectangle_shape_{Point(-1., 2.), 3., 1.5, M_PI / 4};
  RoundedRectangleShape rounded_rectangle_shape_{Point(-1., 2.), 3., 1.5,
                                                 M_PI / 4, 0.5};
  TriangleShape triangle_shape_{Point(-1., 2.), 3., 1.5, M_PI / 4.};
};

TEST_F(ShapesTest, ArcShape) {
  ASSERT_TRUE(arc_shape_.center.isApprox(Vector2d(-1, 2)));
  ASSERT_TRUE(IsEqual(arc_shape_.start_angle, M_PI / 4));
  ASSERT_TRUE(IsEqual(arc_shape_.end_angle, M_PI));
  ASSERT_TRUE(IsEqual(arc_shape_.radius, 2.));
}

TEST_F(ShapesTest, InvalidArcShape) {
  // Invalid radius.
  ASSERT_THROW(ArcShape(Point::Zero(), 0., M_PI / 2, 0.),
               std::invalid_argument);

  // Invalid start and end angles (equal).
  ASSERT_THROW(ArcShape(Point::Zero(), M_PI / 2., M_PI / 2, 1.),
               std::invalid_argument);
}

TEST_F(ShapesTest, CircleShape) {
  ASSERT_TRUE(circle_shape_.center.isApprox(Vector2d(-1, 2)));
  ASSERT_TRUE(IsEqual(circle_shape_.radius, 2.));
}

TEST_F(ShapesTest, InvalidCircleShape) {
  // Invalid radius.
  ASSERT_THROW(CircleShape(Point::Zero(), 0.), std::invalid_argument);
}

TEST_F(ShapesTest, RectangleShape) {
  ASSERT_TRUE(rectangle_shape_.center.isApprox(Vector2d(-1, 2)));
  ASSERT_TRUE(IsEqual(rectangle_shape_.size_x, 3.));
  ASSERT_TRUE(IsEqual(rectangle_shape_.size_y, 1.5));
  ASSERT_TRUE(IsEqual(rectangle_shape_.angle, M_PI / 4));
}

TEST_F(ShapesTest, InvalidRectangleShape) {
  // Invalid size_x.
  ASSERT_THROW(RectangleShape(Point::Zero(), 0., 1., 0.),
               std::invalid_argument);
  // Invalid size_y.
  ASSERT_THROW(RectangleShape(Point::Zero(), 1., 0., 0.),
               std::invalid_argument);
}

TEST_F(ShapesTest, RoundedRectangleShape) {
  ASSERT_TRUE(rounded_rectangle_shape_.center.isApprox(Vector2d(-1, 2)));
  ASSERT_TRUE(IsEqual(rounded_rectangle_shape_.size_x, 3.));
  ASSERT_TRUE(IsEqual(rounded_rectangle_shape_.size_y, 1.5));
  ASSERT_TRUE(IsEqual(rounded_rectangle_shape_.angle, M_PI / 4));
  ASSERT_TRUE(IsEqual(rounded_rectangle_shape_.radius, 0.5));
}

TEST_F(ShapesTest, InvalidRoundedRectangleShape) {
  // Invalid size_x.
  ASSERT_THROW(RoundedRectangleShape(Point::Zero(), 0., 1., 0., 0.1),
               std::invalid_argument);
  // Invalid size_y.
  ASSERT_THROW(RoundedRectangleShape(Point::Zero(), 1., 0., 0., 0.1),
               std::invalid_argument);
  // Invalid radius.
  ASSERT_THROW(RoundedRectangleShape(Point::Zero(), 1., 1., 0., 0.),
               std::invalid_argument);
  // The radius must also be smaller than half of the sizes.
  ASSERT_THROW(RoundedRectangleShape(Point::Zero(), 3., 2., 0., 1.1),
               std::invalid_argument);
  ASSERT_THROW(RoundedRectangleShape(Point::Zero(), 2., 3., 0., 1.1),
               std::invalid_argument);
}

TEST_F(ShapesTest, TriangleShape) {
  ASSERT_TRUE(triangle_shape_.center.isApprox(Vector2d(-1, 2)));
  ASSERT_TRUE(IsEqual(triangle_shape_.base, 3.));
  ASSERT_TRUE(IsEqual(triangle_shape_.height, 1.5));
  ASSERT_TRUE(IsEqual(triangle_shape_.angle, M_PI / 4));
}

TEST_F(ShapesTest, InvalidTriangleShape) {
  // Invalid base.
  ASSERT_THROW(TriangleShape(Point::Zero(), 0., 1., 0.), std::invalid_argument);
  // Invalid height.
  ASSERT_THROW(TriangleShape(Point::Zero(), 1., 0., 0.), std::invalid_argument);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}