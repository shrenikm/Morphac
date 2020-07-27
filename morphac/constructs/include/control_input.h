#ifndef INPUT_H
#define INPUT_H

#include <sstream>
#include <vector>

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class ControlInput {
 public:
  ControlInput(const int size);
  ControlInput(const Eigen::VectorXd& control_input_data);
  ControlInput(std::initializer_list<double> control_input_elements);

  // Copy constructor.
  ControlInput(const ControlInput& control_input) = default;

  // Copy assignment.
  ControlInput& operator=(const ControlInput& control_input) = default;

  ControlInput& operator+=(const ControlInput& control_input);
  ControlInput operator+(const ControlInput& control_input) const;
  ControlInput& operator-=(const ControlInput& control_input);
  ControlInput operator-(const ControlInput& control_input) const;
  ControlInput& operator*=(const double scalar);

  friend bool operator==(const ControlInput& control_input1,
                         const ControlInput& control_input2);
  friend bool operator!=(const ControlInput& control_input1,
                         const ControlInput& control_input2);

  double& operator[](const int index);
  const double& operator[](const int index) const;

  friend std::ostream& operator<<(std::ostream& os,
                                  const ControlInput& control_input);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  int get_size() const;
  const Eigen::VectorXd& get_data() const;
  void set_data(const Eigen::VectorXd& data);
  void set_data(std::initializer_list<double> elements);

  bool IsEmpty() const;
  static ControlInput CreateLike(
      const morphac::constructs::ControlInput& control_input);

 private:
  int size_;
  Eigen::VectorXd data_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
ControlInput operator*(ControlInput control_input, const double scalar);
ControlInput operator*(const double scalar, ControlInput control_input);

}  // namespace constructs
}  // namespace morphac

#endif
