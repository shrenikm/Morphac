#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Eigen/Dense"
#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace environment {

class Map {
 public:
  Map(const double width, const double height, const double resolution);
  Map(const Eigen::MatrixXd& data, const double resolution);

  double get_width() const;
  double get_height() const;
  double get_resolution() const;
  // Get data function for constant Map objects.
  const Eigen::MatrixXd& get_data() const;
  // Get data function for when the data needs to be changed.
  // This is what gets exposed in the python bindings so that we can do inplace
  // numpy operations like map.data[:10, :10] = 0
  Eigen::MatrixXd& get_data_ref();

  void set_data(const Eigen::MatrixXd& data);

 private:
  double width_;
  double height_;
  double resolution_;
  Eigen::MatrixXd data_;
};

}  // namespace environment
}  // namespace morphac

#endif
