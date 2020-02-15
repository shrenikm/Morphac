#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace environments {

class Environment2D {
 public:
  Environment2D(const double width, const double height,
                const double resolution);
  Environment2D(Eigen::MatrixXd map, const double resolution);

  const double get_width();
  const double get_height();
  const double get_resolution();
  const Eigen::MatrixXd& get_map();

  void set_map(Eigen::MatrixXd map);

 private:
  const double width_;
  const double height_;
  const double resolution_;
  Eigen::MatrixXd map_;
};

}  // namespace environments
}  // namespace morphac

#endif

