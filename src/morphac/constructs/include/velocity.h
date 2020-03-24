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
  Velocity operator+(const Velocity& velocity) const;
  Velocity& operator-=(const Velocity& velocity);
  Velocity operator-(const Velocity& velocity) const;
  Velocity& operator*=(const double scalar);

  double& operator()(const int index);
  double operator()(const int index) const;

  friend std::ostream& operator<<(std::ostream& os, const Velocity& velocity);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  int get_size() const;
  const Eigen::VectorXd& get_velocity_vector() const;
  void set_velocity_vector(const Eigen::VectorXd& velocity_vector);

  bool IsEmpty() const;
  static Velocity CreateLike(const morphac::constructs::Velocity& velocity);

 private:
  const int size_;
  Eigen::VectorXd velocity_vector_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
Velocity operator*(Velocity velocity, const double scalar);
Velocity operator*(const double scalar, Velocity velocity);

}  // namespace constructs
}  // namespace morphac

#endif
