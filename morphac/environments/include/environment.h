#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace environments {

class Environment {
 public:
  Environment(const double width, const double height, const double resolution);
  Environment(const Eigen::MatrixXd& map, const double resolution);

  double get_width() const;
  double get_height() const;
  double get_resolution() const;
  const Eigen::MatrixXd& get_map() const;

  void set_map(const Eigen::MatrixXd& map);

 private:
  double width_;
  double height_;
  double resolution_;
  Eigen::MatrixXd map_;
};

}  // namespace environments
}  // namespace morphac

#endif

