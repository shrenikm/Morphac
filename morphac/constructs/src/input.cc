#include "constructs/include/input.h"

namespace morphac {
namespace constructs {

using std::ostream;
using std::ostringstream;
using std::string;
using Eigen::VectorXd;

Input::Input(const int size) : size_(size) {
  MORPH_REQUIRE(size >= 0, std::invalid_argument,
                "Input size is non-positive.");
  input_vector_ = VectorXd::Zero(size);
}

Input::Input(const VectorXd& input_vector)
    : size_(input_vector.size()), input_vector_(input_vector) {
  MORPH_REQUIRE(input_vector.size() >= 0, std::invalid_argument,
                "Input vector size is non-positive.");
}

Input& Input::operator+=(const Input& input) {
  MORPH_REQUIRE(
      this->size_ == input.size_, std::invalid_argument,
      "Inputs are not of the same size. The += operator requires them "
      "to be of the "
      "same size.");
  this->input_vector_ += input.input_vector_;
  return *this;
}

Input Input::operator+(const Input& input) const {
  MORPH_REQUIRE(
      this->size_ == input.size_, std::invalid_argument,
      "Inputs are not of the same size. The + operator requires them "
      "to be of the "
      "same size.");
  Input result(this->size_);
  result.input_vector_ = this->input_vector_ + input.input_vector_;
  return result;
}

Input& Input::operator-=(const Input& input) {
  MORPH_REQUIRE(
      this->size_ == input.size_, std::invalid_argument,
      "Inputs are not of the same size. The -= operator requires them "
      "to be of the "
      "same size.");
  this->input_vector_ -= input.input_vector_;
  return *this;
}

Input Input::operator-(const Input& input) const {
  MORPH_REQUIRE(
      this->size_ == input.size_, std::invalid_argument,
      "Inputs are not of the same size. The - operator requires them "
      "to be of the "
      "same size.");
  Input result(this->size_);
  result.input_vector_ = this->input_vector_ - input.input_vector_;
  return result;
}

Input& Input::operator*=(const double scalar) {
  this->input_vector_ = this->input_vector_ * scalar;
  return *this;
}

// Non-member multiplication functions
Input operator*(Input input, const double scalar) {
  return input *= scalar;
}

Input operator*(const double scalar, Input input) {
  return input *= scalar;
}

double& Input::operator()(const int index) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Input index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Input object is empty");
  return input_vector_(index);
}

double Input::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Input index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Input object is empty");
  return input_vector_(index);
}

ostream& operator<<(ostream& os, const Input& input) {
  os << "Input[" << input.get_input_vector().transpose() << "]";
  return os;
}

string Input::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

bool Input::IsEmpty() const { return size_ == 0; }

int Input::get_size() const { return size_; }

const VectorXd& Input::get_input_vector() const {
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Input object is empty");
  return input_vector_;
}

void Input::set_input_vector(const VectorXd& input_vector) {
  MORPH_REQUIRE(input_vector.size() == size_, std::invalid_argument,
                "Input vector size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Input object is empty");
  input_vector_ = input_vector;
}

Input Input::CreateLike(const Input& input) {
  Input new_input{input.get_size()};
  return new_input;
}

}  // namespace constructs
}  // namespace morphac

