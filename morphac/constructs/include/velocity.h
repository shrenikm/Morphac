#ifndef VELOCITY_H
#define VELOCITY_H

#include <sstream>
#include <vector>

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class Velocity {
 public:
  Velocity(const int size);
  Velocity(const Eigen::VectorXd& data);
  Velocity(std::initializer_list<double> elements);

  // Copy constructor.
  Velocity(const Velocity& velocity) = default;

  // Copy assignment.
  Velocity& operator=(const Velocity& velocity) = default;

  Velocity& operator+=(const Velocity& velocity);
  Velocity operator+(const Velocity& velocity) const;
  Velocity& operator-=(const Velocity& velocity);
  Velocity operator-(const Velocity& velocity) const;
  Velocity& operator*=(const double scalar);

  friend bool operator==(const Velocity& velocity1, const Velocity& velocity2);
  friend bool operator!=(const Velocity& velocity1, const Velocity& velocity2);

  double& operator()(const int index);
  const double& operator()(const int index) const;

  friend std::ostream& operator<<(std::ostream& os, const Velocity& velocity);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  int get_size() const;
  const Eigen::VectorXd& get_data() const;
  void set_data(const Eigen::VectorXd& data);
  void set_data(std::initializer_list<double> elements);

  bool IsEmpty() const;
  static Velocity CreateLike(const morphac::constructs::Velocity& velocity);

 private:
  int size_;
  Eigen::VectorXd data_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
Velocity operator*(Velocity velocity, const double scalar);
Velocity operator*(const double scalar, Velocity velocity);

}  // namespace constructs
}  // namespace morphac

#endif
