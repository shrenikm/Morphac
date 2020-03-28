#ifndef CONTROL_INPUT_H
#define CONTROL_INPUT_H

#include <sstream>

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class ControlInput {
 public:
  ControlInput(const int size = 0);
  ControlInput(const Eigen::VectorXd& input_vector);

  ControlInput& operator+=(const ControlInput& input);
  ControlInput operator+(const ControlInput& input) const;
  ControlInput& operator-=(const ControlInput& input);
  ControlInput operator-(const ControlInput& input) const;
  ControlInput& operator*=(const double scalar);

  double& operator()(const int index);
  double operator()(const int index) const;

  friend std::ostream& operator<<(std::ostream& os, const ControlInput& input);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  int get_size() const;
  const Eigen::VectorXd& get_input_vector() const;
  void set_input_vector(const Eigen::VectorXd& input_vector);

  bool IsEmpty() const;
  static ControlInput CreateLike(
      const morphac::constructs::ControlInput& input);

 private:
  const int size_;
  Eigen::VectorXd input_vector_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
ControlInput operator*(ControlInput input, const double scalar);
ControlInput operator*(const double scalar, ControlInput input);

}  // namespace constructs
}  // namespace morphac

#endif
