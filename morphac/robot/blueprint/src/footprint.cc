#include "robot/blueprint/include/footprint.h"

namespace morphac {
namespace robot {
namespace blueprint {

using morphac::common::aliases::Point;
using morphac::common::aliases::Points;
using morphac::constructs::Coordinate;
using morphac::math::geometry::CreateCircularPolygon;
using morphac::math::geometry::CreateRectangularPolygon;
using morphac::math::geometry::CreateRoundedRectangularPolygon;
using morphac::math::geometry::CreateTriangularPolygon;

Footprint::Footprint(const Points& data) : data_(data) {
  MORPH_REQUIRE(data.rows() > 0, std::invalid_argument,
                "Invalid footprint matrix dimensions. Must be n x 2.");
}

const Points& Footprint::get_data() const { return data_; }

Footprint Footprint::CreateCircularFootprint(const double radius,
                                             const double angular_resolution,
                                             const Point& center) {
  return Footprint(CreateCircularPolygon(radius, angular_resolution, -center));
}

Footprint Footprint::CreateRectangularFootprint(const double size_x,
                                                const double size_y,
                                                const double angle,
                                                const Point& center) {
  return Footprint(CreateRectangularPolygon(size_x, size_y, angle, -center));
}

Footprint Footprint::CreateRoundedRectangularFootprint(
    const double size_x, const double size_y, const double angle,
    const double radius, const double angular_resolution, const Point& center) {
  return Footprint(CreateRoundedRectangularPolygon(
      size_x, size_y, angle, radius, angular_resolution, -center));
}

Footprint Footprint::CreateTriangularFootprint(const double base,
                                               const double height,
                                               const double angle,
                                               const Point& center) {
  return Footprint(CreateTriangularPolygon(base, height, angle, -center));
}

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac
