#ifndef CONTROL_INPUT_H
#define CONTROL_INPUT_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class ControlInput {
 public:
  ControlInput(const int size = 0);
  ControlInput(const Eigen::VectorXd& input_vector);

  ControlInput& operator+=(const ControlInput& input);
  ControlInput operator+(const ControlInput& input);
  ControlInput& operator-=(const ControlInput& input);
  ControlInput operator-(const ControlInput& input);
  ControlInput& operator*=(const double scalar);

  bool is_empty() const;
  const int get_size() const;
  const Eigen::VectorXd& get_input_vector() const;
  double get_input_at(int index) const;
  void set_input_vector(const Eigen::VectorXd& input_vector);
  void set_input_at(int index, double input_element);

 private:
  const int size_;
  Eigen::VectorXd input_vector_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
ControlInput operator*(const double scalar, ControlInput input);
ControlInput operator*(ControlInput input, const double scalar);

}  // namespace constructs
}  // namespace morphac

#endif
