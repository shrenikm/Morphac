#ifndef CONTROL_INPUT_H
#define CONTROL_INPUT_H

#include <sstream>

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class Input {
 public:
  Input(const int size = 0);
  Input(const Eigen::VectorXd& input_vector);
  // Copy constructor.
  Input(const Input& input) = default;

  // Copy assignment.
  Input& operator=(const Input& input) = default;

  Input& operator+=(const Input& input);
  Input operator+(const Input& input) const;
  Input& operator-=(const Input& input);
  Input operator-(const Input& input) const;
  Input& operator*=(const double scalar);

  double& operator()(const int index);
  double operator()(const int index) const;

  friend std::ostream& operator<<(std::ostream& os, const Input& input);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  int get_size() const;
  const Eigen::VectorXd& get_input_vector() const;
  void set_input_vector(const Eigen::VectorXd& input_vector);

  bool IsEmpty() const;
  static Input CreateLike(
      const morphac::constructs::Input& input);

 private:
  int size_;
  Eigen::VectorXd input_vector_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
Input operator*(Input input, const double scalar);
Input operator*(const double scalar, Input input);

}  // namespace constructs
}  // namespace morphac

#endif