#include "constructs/include/control_input.h"

namespace morphac {
namespace constructs {

using Eigen::VectorXd;

ControlInput::ControlInput(int size) : size_(size) {
  MORPH_REQUIRE(size > 0, std::invalid_argument,
                "Control input size is non-positive.");
  control_input_ = VectorXd::Zero(size);
}

ControlInput::ControlInput(VectorXd input) {
  MORPH_REQUIRE(input.size() > 0, std::invalid_argument,
                "Control input size is non-positive.");
  size_ = input.size();
  control_input_ = input;
}

ControlInput::ControlInput(const ControlInput& input) {
  this->size_ = input.size_;
  this->control_input_ = input.control_input_;
}

int ControlInput::get_size() { return size_; }

VectorXd ControlInput::get_input() { return control_input_; }

double ControlInput::get_input(int index) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Control input index out of bounds.");
  return control_input_(index);
}

void ControlInput::set_input(VectorXd input) {
  MORPH_REQUIRE(input.size() > 0, std::invalid_argument,
                "Control input size is non-positive.");
  size_ = input.size();
  control_input_ = input;
}

void ControlInput::set_input(int index, double input_element) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Control input index out of bounds.");
  control_input_(index) = input_element;
}

}  // namespace constructs
}  // namespace morphac

