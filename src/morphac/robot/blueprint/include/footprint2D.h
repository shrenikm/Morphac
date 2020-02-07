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
    Footprint2D(const Footprint2D& footprint2D) = delete;
    Footprint2D& operator=(const Footprint2D& footprint2D) = delete;


    const Eigen::MatrixXd& get_footprint_matrix() const;

  private:
    const Eigen::MatrixXd& footprint_matrix_;

};


} // namespace models
} // namespace robot
} // namespace morphac

#endif
