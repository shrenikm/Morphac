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

  // Footprint generating functions. Note that the coordinates are always with
  // respect to the origin. The relative center is the position of the center
  // of the footprint within the footprint (It is measured from (0, 0)). So,
  // even if a center is provided, the footprint is shifted such that the
  // relative center coincides with (0, 0).
  static Footprint CreateCircularFootprint(
      const double radius, const double angular_resolution,
      const morphac::common::aliases::Point& relative_center =
          morphac::common::aliases::Point::Zero());

  static Footprint CreateRectangularFootprint(
      const double size_x, const double size_y, const double angle,
      const morphac::common::aliases::Point& relative_center =
          morphac::common::aliases::Point::Zero());

  static Footprint CreateRoundedRectangularFootprint(
      const double size_x, const double size_y, const double angle,
      const double radius, const double angular_resolution,
      const morphac::common::aliases::Point& relative_center =
          morphac::common::aliases::Point::Zero());

  static Footprint CreateTriangularFootprint(
      const double base, const double height, const double angle,
      const morphac::common::aliases::Point& relative_center =
          morphac::common::aliases::Point::Zero());

 private:
  morphac::common::aliases::Points data_;
};

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

#endif
