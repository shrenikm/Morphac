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

  int get_size();
  Eigen::VectorXd get_input();
  double get_input(int index);
  void set_input(Eigen::VectorXd input);
  void set_input(int index, double input_element);

 private:
  int size_;
  Eigen::VectorXd control_input_;
};

}  // namespace constructs
}  // namespace morphac

#endif
