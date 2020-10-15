#include "robot/blueprint/include/footprint.h"

namespace morphac {
namespace robot {
namespace blueprint {

using morphac::common::aliases::BoundingBox;
using morphac::common::aliases::Point;
using morphac::common::aliases::Points;
using morphac::constructs::Coordinate;
using morphac::math::geometry::CircleShape;
using morphac::math::geometry::ComputeBoundingBox;
using morphac::math::geometry::CreateCircularPolygon;
using morphac::math::geometry::CreateRectangularPolygon;
using morphac::math::geometry::CreateRoundedRectangularPolygon;
using morphac::math::geometry::CreateTriangularPolygon;
using morphac::math::geometry::RectangleShape;
using morphac::math::geometry::RoundedRectangleShape;
using morphac::math::geometry::TriangleShape;

Footprint::Footprint(const Points& data) : data_(data) {
  MORPH_REQUIRE(data.rows() > 0, std::invalid_argument,
                "Invalid footprint matrix dimensions. Must be n x 2.");
  bounding_box_ = ComputeBoundingBox(data);
}

const Points& Footprint::get_data() const { return data_; }

const BoundingBox& Footprint::get_bounding_box() const { return bounding_box_; }

// Note that as these are relative centers, we create new shape with the center
// negated to obtain the desired effect
Footprint Footprint::CreateCircularFootprint(const CircleShape& circle_shape,
                                             const double angular_resolution) {
  return Footprint(CreateCircularPolygon(
      CircleShape{circle_shape.radius, -circle_shape.center},
      angular_resolution));
}  // namespace blueprint

Footprint Footprint::CreateRectangularFootprint(
    const RectangleShape& rectangle_shape) {
  return Footprint(CreateRectangularPolygon(
      RectangleShape{rectangle_shape.size_x, rectangle_shape.size_y,
                     rectangle_shape.angle, -rectangle_shape.center}));
}

Footprint Footprint::CreateRoundedRectangularFootprint(
    const RoundedRectangleShape& rounded_rectangle_shape,
    const double angular_resolution) {
  return Footprint(CreateRoundedRectangularPolygon(
      RoundedRectangleShape{
          rounded_rectangle_shape.size_x, rounded_rectangle_shape.size_y,
          rounded_rectangle_shape.angle, rounded_rectangle_shape.radius,
          -rounded_rectangle_shape.center},
      angular_resolution));
}

Footprint Footprint::CreateTriangularFootprint(
    const TriangleShape& triangle_shape) {
  return Footprint(CreateTriangularPolygon(
      TriangleShape{triangle_shape.base, triangle_shape.height,
                    triangle_shape.angle, -triangle_shape.center}));
}

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac
