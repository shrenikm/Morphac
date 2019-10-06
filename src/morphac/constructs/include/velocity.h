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

  int get_size();
  Eigen::VectorXd get_velocity();
  double get_velocity(int index);
  void set_velocity(Eigen::VectorXd velocity);
  void set_velocity(int index, double velocity_element);

 private:
  int size_;
  Eigen::VectorXd velocity_;
};

}  // namespace constructs
}  // namespace morphac

#endif
