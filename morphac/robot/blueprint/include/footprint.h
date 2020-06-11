#ifndef FOOTPRINT_H
#define FOOTPRINT_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace robot {
namespace blueprint {

class Footprint {
 public:
  Footprint(const Eigen::MatrixXd& footprint_matrix);

  const Eigen::MatrixXd& get_footprint_matrix() const;

 private:
  Eigen::MatrixXd footprint_matrix_;
};

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

#endif
