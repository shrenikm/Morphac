#include "constructs/include/control_input.h"

namespace morphac {
namespace constructs {

using Eigen::VectorXd;

ControlInput::ControlInput(int size)
    : size_(size), control_input_(VectorXd::Zero(size)) {
  MORPH_REQUIRE(size > 0, std::invalid_argument,
                "Control input size is non-positive.");
}

ControlInput::ControlInput(VectorXd input)
    : size_(input.size()), control_input_(input) {
  MORPH_REQUIRE(input.size() > 0, std::invalid_argument,
                "Control input size is non-positive.");
}

ControlInput::ControlInput(const ControlInput& input)
    : size_(input.size_), control_input_(input.control_input_) {}

const int ControlInput::get_size() const { return size_; }

const VectorXd& ControlInput::get_input() const { return control_input_; }

double ControlInput::get_input(int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Control input index out of bounds.");
  return control_input_(index);
}

void ControlInput::set_input(const VectorXd& input) {
  MORPH_REQUIRE(input.size() == size_, std::invalid_argument,
                "Control input and vector sizes do not match.");
  control_input_ = input;
}

void ControlInput::set_input(int index, double input_element) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Control input index out of bounds.");
  control_input_(index) = input_element;
}

}  // namespace constructs
}  // namespace morphac

