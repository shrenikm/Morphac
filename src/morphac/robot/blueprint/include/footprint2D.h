#ifndef FOOTPRINT2D_H
#define FOOTPRINT2D_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace robot {
namespace blueprint {

class Footprint2D {
  public:
    Footprint2D(const Eigen::MatrixXd& footprint_matrix);

    const Eigen::MatrixXd& get_footprint_matrix() const;

  private:
    const Eigen::MatrixXd& footprint_matrix_;

};


} // namespace blueprint
} // namespace robot
} // namespace morphac

#endif
