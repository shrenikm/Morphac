#ifndef VELOCITY_H
#define VELOCITY_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class Velocity {
 public:
  Velocity(int size);
  Velocity(Eigen::VectorXd velocity);
  Velocity(const Velocity& velocity);

  int get_size() const;
  const Eigen::VectorXd& get_velocity() const;
  double get_velocity(int index) const;
  void set_velocity(const Eigen::VectorXd& velocity);
  void set_velocity(int index, double velocity_element);

 private:
  const int size_;
  Eigen::VectorXd velocity_;
};

}  // namespace constructs
}  // namespace morphac

#endif
