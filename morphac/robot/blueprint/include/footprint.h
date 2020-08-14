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

  static Footprint OffsetFootprint(const Footprint& footprint,
                                   const Eigen::Vector2d& center);
  static Footprint OffsetFootprint(
      const Footprint& footprint,
      const morphac::constructs::Coordinate& center);

  static Footprint CreateRectangularFootprint(
      const double size_x, const double size_y,
      const Eigen::Vector2d& center = Eigen::Vector2d::Zero());
  static Footprint CreateRectangularFootprint(
      const double size_x, const double size_y,
      const morphac::constructs::Coordinate& center =
          morphac::constructs::Coordinate());

  static Footprint CreateCircularFootprint(
      const double radius, const double angular_resolution,
      const Eigen::Vector2d& center = Eigen::Vector2d::Zero());
  static Footprint CreateCircularFootprint(
      const double radius, const double angular_resolution,
      const morphac::constructs::Coordinate& center =
          morphac::constructs::Coordinate());

  static Footprint CreateRoundedRectangularFootprint(
      const double size_x, const double size_y, const double radius,
      const double angular_resolution,
      const Eigen::Vector2d& center = Eigen::Vector2d::Zero());
  static Footprint CreateRoundedRectangularFootprint(
      const double size_x, const double size_y, const double radius,
      const double angular_resolution,
      const morphac::constructs::Coordinate& center =
          morphac::constructs::Coordinate());

 private:
  Eigen::MatrixXd data_;
};

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

#endif
