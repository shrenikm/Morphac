#ifndef FOOTPRINT_H
#define FOOTPRINT_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"
#include "constructs/include/coordinate.h"

namespace morphac {
namespace robot {
namespace blueprint {

class Footprint {
 public:
  Footprint(const Eigen::MatrixXd& data);

  // Copy constructor.
  Footprint(const Footprint& footprint) = default;

  // Copy assignment.
  Footprint& operator=(const Footprint& footprint) = default;

  const Eigen::MatrixXd& get_data() const;

  static Footprint OffsetFootprint(
      const Footprint& footprint,
      const morphac::constructs::Coordinate& center_offset);

  static Footprint CreateRectangularFootprint(
      const double size_x, const double size_y,
      const morphac::constructs::Coordinate& center_offset);
  static Footprint CreateStadiumFootprint(
      const double size_x, const double size_y, const double radius,
      const morphac::constructs::Coordinate& center_offset);
  static Footprint CreateCircularFootprint(
      const double radius, const double resolution,
      const morphac::constructs::Coordinate& center_offset);

 private:
  Eigen::MatrixXd data_;
};

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

#endif
