#include "math/geometry/include/polygons.h"

namespace morphac {
namespace math {
namespace geometry {

using std::fabs;

using Eigen::VectorXd;

using morphac::common::aliases::Point;
using morphac::common::aliases::Points;
using morphac::math::geometry::ArcShape;
using morphac::math::geometry::CircleShape;
using morphac::math::geometry::RectangleShape;
using morphac::math::geometry::RoundedRectangleShape;
using morphac::math::geometry::TriangleShape;
using morphac::math::transforms::TransformPoints;

Points CreateArc(const ArcShape& arc_shape, const double angular_resolution) {
  MORPH_REQUIRE(angular_resolution > 0, std::invalid_argument,
                "Angular resolution must be positive.");
  // We have num_points * angular_resolution = 2 * pi (360 degrees).
  int num_points = std::round(
      fabs(arc_shape.end_angle - arc_shape.start_angle) / angular_resolution);

  Points arc(num_points, 2);

  VectorXd angles = VectorXd::LinSpaced(num_points, arc_shape.start_angle,
                                        arc_shape.end_angle);

  VectorXd x_coordinates =
      arc_shape.radius * Eigen::cos(angles.array()).matrix();
  VectorXd y_coordinates =
      arc_shape.radius * Eigen::sin(angles.array()).matrix();

  arc.col(0) = x_coordinates;
  arc.col(1) = y_coordinates;

  return TransformPoints(arc, 0., arc_shape.center);
}

Points CreateCircularPolygon(const CircleShape& circle_shape,
                             const double angular_resolution) {
  MORPH_REQUIRE(angular_resolution > 0, std::invalid_argument,
                "Angular resolution must be positive.");
  // A circle is basically an arc from 0 to 2 * pi. We make sure that both 0 and
  // 2 * pi isn't included as we don't want duplicate corners in the polygon.
  ArcShape arc_shape{0., 2 * M_PI - angular_resolution, circle_shape.radius,
                     circle_shape.center};
  return CreateArc(arc_shape, angular_resolution);
}

Points CreateRectangularPolygon(const RectangleShape& rectangle_shape) {
  Points polygon(4, 2);
  polygon << -rectangle_shape.size_x / 2, rectangle_shape.size_y / 2,
      rectangle_shape.size_x / 2, rectangle_shape.size_y / 2,
      rectangle_shape.size_x / 2, -rectangle_shape.size_y / 2,
      -rectangle_shape.size_x / 2, -rectangle_shape.size_y / 2;

  return TransformPoints(polygon, rectangle_shape.angle,
                         rectangle_shape.center);
}

Points CreateRoundedRectangularPolygon(
    const RoundedRectangleShape& rounded_rectangle_shape,
    const double angular_resolution) {
  MORPH_REQUIRE(angular_resolution > 0, std::invalid_argument,
                "Angular resolution must be positive.");
  // The rounded rectangle is basically just the four arcs that form the
  // corners of the shape.

  Points centers = CreateRectangularPolygon(RectangleShape{
      rounded_rectangle_shape.size_x - 2 * rounded_rectangle_shape.radius,
      rounded_rectangle_shape.size_y - 2 * rounded_rectangle_shape.radius, 0.,
      Point::Zero()});

  Points arc1 =
      CreateArc(ArcShape{M_PI, M_PI / 2, rounded_rectangle_shape.radius,
                         centers.row(0).transpose()},
                angular_resolution);
  Points arc2 = CreateArc(ArcShape{M_PI / 2, 0, rounded_rectangle_shape.radius,
                                   centers.row(1).transpose()},
                          angular_resolution);
  Points arc3 = CreateArc(ArcShape{0, -M_PI / 2, rounded_rectangle_shape.radius,
                                   centers.row(2).transpose()},
                          angular_resolution);
  Points arc4 =
      CreateArc(ArcShape{-M_PI / 2, -M_PI, rounded_rectangle_shape.radius,
                         centers.row(3).transpose()},
                angular_resolution);

  Points polygon(arc1.rows() + arc2.rows() + arc3.rows() + arc4.rows(), 2);
  polygon << arc1, arc2, arc3, arc4;

  return TransformPoints(polygon, rounded_rectangle_shape.angle,
                         rounded_rectangle_shape.center);
}

Points CreateTriangularPolygon(const TriangleShape& triangle_shape) {
  Points polygon(3, 2);
  polygon << 0., triangle_shape.height / 2, triangle_shape.base / 2,
      -triangle_shape.height / 2, -triangle_shape.base / 2,
      -triangle_shape.height / 2;

  return TransformPoints(polygon, triangle_shape.angle, triangle_shape.center);
}

bool IsPointInsidePolygon(const Points& polygon, const Point& point) {
  // The algorithm is based off:
  // http://www.jeffreythompson.org/collision-detection/poly-point.php
  // which originates from:
  // https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
  for (int i = 0; i < polygon.rows(); ++i) {
    j = (i + 1) % polygon.rows();

    bool inside = false;
    if (((polygon(i, 1) > point(1)) != (polygon(j, 1) > point(1))) &&
        (point(0) <
         (polygon(j, 0) -
          polygon(i, 0) *
              (point(1) - polygon(i, 1) / (polygon(j, 1) - polygon(i, 1) +
                                           polygon(i, 0)))))) {
      inside = !inside;
    }
  }

  return inside;
}
}  // namespace geometry

}  // namespace math
}  // namespace morphac
}  // namespace morphac
