#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Eigen/Dense"

#include "common/include/error_macros.h"

namespace morphac {
namespace environments {

class Environment2D {
 public:
  Environment2D(int width, int height, int origin_x = 0, int origin_y = 0);
  Environment2D(Eigen::MatrixXd map, int origin_x = 0, int origin_y = 0);

  int get_width();
  int get_height();
  Eigen::MatrixXd get_map();

 private:
  int width_;
  int height_;
  int origin_x_;
  int origin_y_;
  Eigen::MatrixXd map_;
};

}  // namespace environments
}  // namespace morphac

#endif

