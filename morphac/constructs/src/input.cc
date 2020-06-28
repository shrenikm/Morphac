#include "constructs/include/input.h"

namespace morphac {
namespace constructs {

using std::initializer_list;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

using Eigen::Map;
using Eigen::VectorXd;

Input::Input(const int size) : size_(size) {
  MORPH_REQUIRE(size >= 0, std::invalid_argument,
                "Input size is non-positive.");
  input_data_ = VectorXd::Zero(size);
}

Input::Input(const VectorXd& input_data)
    : size_(input_data.size()), input_data_(input_data) {
  MORPH_REQUIRE(input_data.size() >= 0, std::invalid_argument,
                "Input data size is non-positive.");
}

Input::Input(initializer_list<double> input_elements)
    : size_(input_elements.size()) {
  // As it is an initializer list, the size is always going to be >= 0 and need
  // not be checked.
  vector<double> input_data_vector(input_elements);
  input_data_ = Map<VectorXd>(&input_data_vector[0], size_);
}

Input& Input::operator+=(const Input& input) {
  MORPH_REQUIRE(
      this->size_ == input.size_, std::invalid_argument,
      "Inputs are not of the same size. The += operator requires them "
      "to be of the "
      "same size.");
  this->input_data_ += input.input_data_;
  return *this;
}

Input Input::operator+(const Input& input) const {
  MORPH_REQUIRE(this->size_ == input.size_, std::invalid_argument,
                "Inputs are not of the same size. The + operator requires them "
                "to be of the "
                "same size.");
  Input result(this->size_);
  result.input_data_ = this->input_data_ + input.input_data_;
  return result;
}

Input& Input::operator-=(const Input& input) {
  MORPH_REQUIRE(
      this->size_ == input.size_, std::invalid_argument,
      "Inputs are not of the same size. The -= operator requires them "
      "to be of the "
      "same size.");
  this->input_data_ -= input.input_data_;
  return *this;
}

Input Input::operator-(const Input& input) const {
  MORPH_REQUIRE(this->size_ == input.size_, std::invalid_argument,
                "Inputs are not of the same size. The - operator requires them "
                "to be of the "
                "same size.");
  Input result(this->size_);
  result.input_data_ = this->input_data_ - input.input_data_;
  return result;
}

Input& Input::operator*=(const double scalar) {
  this->input_data_ = this->input_data_ * scalar;
  return *this;
}

// Non-member multiplication functions
Input operator*(Input input, const double scalar) { return input *= scalar; }

Input operator*(const double scalar, Input input) { return input *= scalar; }

bool operator==(const Input& input1, const Input& input2) {
  // Two inputs are equal if they are of the same size and their data values
  // are equal.
  if (input1.size_ == input2.size_) {
    if (input1.input_data_.isApprox(input2.input_data_, 1e-6)) {
      return true;
    }
  }
  return false;
}

bool operator!=(const Input& input1, const Input& input2) {
  return !(input1 == input2);
}

double& Input::operator()(const int index) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Input index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Input object is empty");
  return input_data_(index);
}

double Input::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Input index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Input object is empty");
  return input_data_(index);
}

ostream& operator<<(ostream& os, const Input& input) {
  os << "Input[" << input.get_input_data().transpose() << "]";
  return os;
}

string Input::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

bool Input::IsEmpty() const { return size_ == 0; }

int Input::get_size() const { return size_; }

const VectorXd& Input::get_input_data() const {
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Input object is empty");
  return input_data_;
}

void Input::set_input_data(const VectorXd& input_data) {
  MORPH_REQUIRE(input_data.size() == size_, std::invalid_argument,
                "Input data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Input object is empty");
  input_data_ = input_data;
}

void Input::set_input_data(initializer_list<double> input_elements) {
  MORPH_REQUIRE((int)input_elements.size() == size_, std::invalid_argument,
                "Input data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Input object is empty");
  vector<double> input_data_vector(input_elements);
  input_data_ = Map<VectorXd>(&input_data_vector[0], size_);
}

Input Input::CreateLike(const Input& input) {
  Input new_input(input.get_size());
  return new_input;
}

}  // namespace constructs
}  // namespace morphac

