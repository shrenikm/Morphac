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

 private:
  Eigen::MatrixXd data_;
};

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

#endif
