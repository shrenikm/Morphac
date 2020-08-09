#ifndef FOOTPRINT_H
#define FOOTPRINT_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace robot {
namespace blueprint {

class Footprint {
 public:
  Footprint(const Eigen::MatrixXd& data);

  const Eigen::MatrixXd& get_data() const;

  static Footprint CreateRectangularFootprint(const double size_x,
                                              const double size_y);
  static Footprint CreateStadiumFootprint(const double size_x,
                                          const double size_y,
                                          const double radius);
  static Footprint CreateCircularFootprint(const double radius,
                                           const double resolution);

 private:
  Eigen::MatrixXd data_;
};

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

#endif
