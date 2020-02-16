#ifndef VELOCITY_H
#define VELOCITY_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class Velocity {
 public:
  Velocity(const int size = 0);
  Velocity(const Eigen::VectorXd& velocity_vector);

  Velocity& operator+=(const Velocity& velocity);
  Velocity operator+(const Velocity& velocity);
  Velocity& operator-=(const Velocity& velocity);
  Velocity operator-(const Velocity& velocity);
  Velocity& operator*=(const double scalar);

  bool is_empty() const;
  const int get_size() const;
  const Eigen::VectorXd& get_velocity_vector() const;
  double get_velocity_at(int index) const;
  void set_velocity_vector(const Eigen::VectorXd& velocity_vector);
  void set_velocity_at(int index, double velocity_element);

 private:
  const int size_;
  Eigen::VectorXd velocity_vector_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
Velocity operator*(const double scalar, Velocity velocity);
Velocity operator*(Velocity velocity, const double scalar);

}  // namespace constructs
}  // namespace morphac

#endif
