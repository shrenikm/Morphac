#ifndef CONTROL_INPUT_H
#define CONTROL_INPUT_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class ControlInput {
 public:
  ControlInput(int size);
  ControlInput(Eigen::VectorXd input);
  ControlInput(const ControlInput& input);

  int get_size() const;
  const Eigen::VectorXd& get_input() const;
  double get_input(int index) const;
  void set_input(const Eigen::VectorXd& input);
  void set_input(int index, double input_element);

 private:
  const int size_;
  Eigen::VectorXd control_input_;
};

}  // namespace constructs
}  // namespace morphac

#endif
