#ifndef FOOTPRINT_H
#define FOOTPRINT_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"
#include "constructs/include/coordinate.h"
#include "math/geometry/include/polygons.h"
#include "math/transforms/include/transforms.h"

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

  // Footprint generating functions. Note that the coordinates are always with
  // respect to the origin. The relative center is the position of the center
  // of the footprint within the footprint (It is measured from (0, 0)). So,
  // even if a center is provided, the footprint is shifted such that the
  // relative center coincides with (0, 0).
  static Footprint CreateCircularFootprint(
      const double radius, const double angular_resolution,
      const Eigen::Vector2d& relative_center = Eigen::Vector2d::Zero());

  static Footprint CreateRectangularFootprint(
      const double size_x, const double size_y, const double angle,
      const Eigen::Vector2d& relative_center = Eigen::Vector2d::Zero());

  static Footprint CreateRoundedRectangularFootprint(
      const double size_x, const double size_y, const double angle,
      const double radius, const double angular_resolution,
      const Eigen::Vector2d& relative_center = Eigen::Vector2d::Zero());

  static Footprint CreateTriangularFootprint(
      const double base, const double height, const double angle,
      const Eigen::Vector2d& relative_center = Eigen::Vector2d::Zero());

 private:
  Eigen::MatrixXd data_;
};

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

#endif
