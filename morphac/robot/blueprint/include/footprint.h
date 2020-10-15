#ifndef FOOTPRINT_H
#define FOOTPRINT_H

#include "Eigen/Dense"
#include "common/aliases/include/eigen_aliases.h"
#include "common/error_handling/include/error_macros.h"
#include "constructs/include/coordinate.h"
#include "math/geometry/include/polygons.h"

namespace morphac {
namespace robot {
namespace blueprint {

class Footprint {
 public:
  Footprint(const morphac::common::aliases::Points& data);

  // Copy constructor.
  Footprint(const Footprint& footprint) = default;

  // Copy assignment.
  Footprint& operator=(const Footprint& footprint) = default;

  const morphac::common::aliases::Points& get_data() const;

  const morphac::common::aliases::BoundingBox& get_bounding_box() const;

  // Footprint generating functions. Note that the coordinates are always with
  // respect to the origin. The center in these shapes is the relative center
  // which is the position of the center of the footprint within the footprint
  // (It is measured from (0, 0)). So, even if a center is provided, the
  // footprint is shifted such that the center coincides with (0, 0).
  static Footprint CreateCircularFootprint(
      const morphac::math::geometry::CircleShape& circle_shape,
      const double angular_resolution);

  static Footprint CreateRectangularFootprint(
      const morphac::math::geometry::RectangleShape& rectangle_shape);

  static Footprint CreateRoundedRectangularFootprint(
      const morphac::math::geometry::RoundedRectangleShape&
          rounded_rectangle_shape,
      const double angular_resolution);

  static Footprint CreateTriangularFootprint(
      const morphac::math::geometry::TriangleShape& triangle_shape);

 private:
  morphac::common::aliases::Points data_;
  morphac::common::aliases::BoundingBox bounding_box_;
};

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

#endif
