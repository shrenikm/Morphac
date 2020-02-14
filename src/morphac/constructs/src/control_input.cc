#include "constructs/include/control_input.h"

namespace morphac {
namespace constructs {

using Eigen::VectorXd;

ControlInput::ControlInput(const int size) : size_(size) {
  MORPH_REQUIRE(size > 0, std::invalid_argument,
                "Control input size is non-positive.");
  input_vector_ = VectorXd::Zero(size);
}

ControlInput::ControlInput(const VectorXd& input_vector)
    : size_(input_vector.size()), input_vector_(input_vector) {
  MORPH_REQUIRE(input_vector.size() > 0, std::invalid_argument,
                "Control input vector size is non-positive.");
}

ControlInput& ControlInput::operator+=(const ControlInput& input) {
  MORPH_REQUIRE(
      this->size_ == input.size_, std::invalid_argument,
      "Control inputs are not of the same size. The += operator requires them "
      "to be of the "
      "same size.");
  this->input_vector_ += input.input_vector_;
  return *this;
}

ControlInput ControlInput::operator+(const ControlInput& input) {
  MORPH_REQUIRE(
      this->size_ == input.size_, std::invalid_argument,
      "Control inputs are not of the same size. The + operator requires them "
      "to be of the "
      "same size.");
  ControlInput result(this->size_);
  result.input_vector_ = this->input_vector_ + input.input_vector_;
  return result;
}

ControlInput& ControlInput::operator-=(const ControlInput& input) {
  MORPH_REQUIRE(
      this->size_ == input.size_, std::invalid_argument,
      "Control inputs are not of the same size. The -= operator requires them "
      "to be of the "
      "same size.");
  this->input_vector_ -= input.input_vector_;
  return *this;
}

ControlInput ControlInput::operator-(const ControlInput& input) {
  MORPH_REQUIRE(
      this->size_ == input.size_, std::invalid_argument,
      "Control inputs are not of the same size. The - operator requires them "
      "to be of the "
      "same size.");
  ControlInput result(this->size_);
  result.input_vector_ = this->input_vector_ - input.input_vector_;
  return result;
}

ControlInput& ControlInput::operator*=(const double scalar) {
  this->input_vector_ = this->input_vector_ * scalar;
  return *this;
}

// Non-member multiplication functions
ControlInput operator*(ControlInput input, const double scalar) {
  return input *= scalar;
}

ControlInput operator*(const double scalar, ControlInput input) {
  return input *= scalar;
}

const int ControlInput::get_size() const { return size_; }

const VectorXd& ControlInput::get_input_vector() const { return input_vector_; }

double ControlInput::get_input_at(int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Control input index out of bounds.");
  return input_vector_(index);
}

void ControlInput::set_input_vector(const VectorXd& input_vector) {
  MORPH_REQUIRE(input_vector.size() == size_, std::invalid_argument,
                "Control input vector size is incorrect.");
  input_vector_ = input_vector;
}

void ControlInput::set_input_at(int index, double input_element) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Control input index out of bounds.");
  input_vector_(index) = input_element;
}

}  // namespace constructs
}  // namespace morphac

