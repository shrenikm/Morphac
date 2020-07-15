#include "constructs/include/control_input.h"

namespace morphac {
namespace constructs {

using std::initializer_list;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

using Eigen::Map;
using Eigen::VectorXd;

ControlInput::ControlInput(const int size) : size_(size) {
  MORPH_REQUIRE(size >= 0, std::invalid_argument,
                "ControlInput size is non-positive.");
  data_ = VectorXd::Zero(size);
}

ControlInput::ControlInput(const VectorXd& data)
    : size_(data.size()), data_(data) {
  MORPH_REQUIRE(data.size() >= 0, std::invalid_argument,
                "ControlInput data size is non-positive.");
}

ControlInput::ControlInput(initializer_list<double> control_input_elements)
    : size_(control_input_elements.size()) {
  // As it is an initializer list, the size is always going to be >= 0 and need
  // not be checked.
  vector<double> data_vector(control_input_elements);
  data_ = Map<VectorXd>(&data_vector[0], size_);
}

ControlInput& ControlInput::operator+=(const ControlInput& control_input) {
  MORPH_REQUIRE(
      this->size_ == control_input.size_, std::invalid_argument,
      "Control inputs are not of the same size. The += operator requires them "
      "to be of the same size.");
  this->data_ += control_input.data_;
  return *this;
}

ControlInput ControlInput::operator+(const ControlInput& control_input) const {
  // Argument validation happens in the += function call.
  ControlInput result(*this);
  result += control_input;
  return result;
}

ControlInput& ControlInput::operator-=(const ControlInput& control_input) {
  MORPH_REQUIRE(
      this->size_ == control_input.size_, std::invalid_argument,
      "Control inputs are not of the same size. The -= operator requires them "
      "to be of the same size.");
  this->data_ -= control_input.data_;
  return *this;
}

ControlInput ControlInput::operator-(const ControlInput& control_input) const {
  // Argument validation happens in the -= function call.
  ControlInput result(*this);
  result -= control_input;
  return result;
}

ControlInput& ControlInput::operator*=(const double scalar) {
  this->data_ = this->data_ * scalar;
  return *this;
}

// Non-member multiplication functions
ControlInput operator*(ControlInput control_input, const double scalar) {
  return control_input *= scalar;
}

ControlInput operator*(const double scalar, ControlInput control_input) {
  return control_input *= scalar;
}

bool operator==(const ControlInput& control_input1,
                const ControlInput& control_input2) {
  // Two control inputs are equal if they are of the same size and their data
  // values
  // are equal.
  if (control_input1.size_ == control_input2.size_) {
    if (control_input1.data_.isApprox(control_input2.data_, 1e-6)) {
      return true;
    }
  }
  return false;
}

bool operator!=(const ControlInput& control_input1,
                const ControlInput& control_input2) {
  return !(control_input1 == control_input2);
}

double& ControlInput::operator()(const int index) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "ControlInput index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "ControlInput object is empty");
  return data_(index);
}

double ControlInput::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "ControlInput index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "ControlInput object is empty");
  return data_(index);
}

ostream& operator<<(ostream& os, const ControlInput& control_input) {
  os << "ControlInput[" << control_input.get_data().transpose() << "]";
  return os;
}

string ControlInput::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

bool ControlInput::IsEmpty() const { return size_ == 0; }

int ControlInput::get_size() const { return size_; }

const VectorXd& ControlInput::get_data() const {
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "ControlInput object is empty");
  return data_;
}

void ControlInput::set_data(const VectorXd& data) {
  MORPH_REQUIRE(data.size() == size_, std::invalid_argument,
                "ControlInput data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "ControlInput object is empty");
  data_ = data;
}

void ControlInput::set_data(initializer_list<double> control_input_elements) {
  MORPH_REQUIRE((int)control_input_elements.size() == size_,
                std::invalid_argument, "ControlInput data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "ControlInput object is empty");
  vector<double> data_vector(control_input_elements);
  data_ = Map<VectorXd>(&data_vector[0], size_);
}

ControlInput ControlInput::CreateLike(const ControlInput& control_input) {
  ControlInput new_control_input(control_input.get_size());
  return new_control_input;
}

}  // namespace constructs
}  // namespace morphac

