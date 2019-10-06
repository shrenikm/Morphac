#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace environments {

class Environment2D {
 public:
  Environment2D(int width, int height);
  Environment2D(Eigen::MatrixXd map);

  int get_width();
  int get_height();
  Eigen::MatrixXd get_map();

  void set_map(Eigen::MatrixXd map);

 private:
  int width_;
  int height_;
  Eigen::MatrixXd map_;
};

}  // namespace environments
}  // namespace morphac

#endif

