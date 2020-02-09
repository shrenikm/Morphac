#ifndef VELOCITY_H
#define VELOCITY_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class Velocity {
 public:
  Velocity(int size);
  Velocity(const Eigen::VectorXd& velocity_vector);

  const int get_size() const;
  const Eigen::VectorXd& get_velocity_vector() const;
  double get_velocity_at(int index) const;
  void set_velocity_vector(const Eigen::VectorXd& velocity_vector);
  void set_velocity_at(int index, double velocity_element);

 private:
  const int size_;
  Eigen::VectorXd velocity_vector_;
};

}  // namespace constructs
}  // namespace morphac

#endif
