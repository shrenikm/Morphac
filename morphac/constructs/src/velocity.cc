#include "constructs/include/velocity.h"

namespace morphac {
namespace constructs {

using std::initializer_list;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

using Eigen::Map;
using Eigen::VectorXd;

Velocity::Velocity(const int size) : size_(size) {
  MORPH_REQUIRE(size >= 0, std::invalid_argument,
                "Velocity size is non-positive.");
  data_ = VectorXd::Zero(size);
}

Velocity::Velocity(const VectorXd& data) : size_(data.size()), data_(data) {
  MORPH_REQUIRE(data.size() >= 0, std::invalid_argument,
                "Velocity data size is non-positive.");
}

Velocity::Velocity(initializer_list<double> elements) : size_(elements.size()) {
  // As it is an initializer list, the size is always going to be >= 0 and need
  // not be checked.
  vector<double> data_vector(elements);
  data_ = Map<VectorXd>(&data_vector[0], size_);
}

Velocity& Velocity::operator+=(const Velocity& velocity) {
  MORPH_REQUIRE(
      this->size_ == velocity.size_, std::invalid_argument,
      "Velocities are not of the same size. The += operator requires them "
      "to be of the "
      "same size.");
  this->data_ += velocity.data_;
  return *this;
}

Velocity Velocity::operator+(const Velocity& velocity) const {
  // Argument validation happens in the += function call.
  Velocity result(*this);
  result += velocity;
  return result;
}

Velocity& Velocity::operator-=(const Velocity& velocity) {
  MORPH_REQUIRE(
      this->size_ == velocity.size_, std::invalid_argument,
      "Velocities are not of the same size. The -= operator requires them "
      "to be of the "
      "same size.");
  this->data_ -= velocity.data_;
  return *this;
}

Velocity Velocity::operator-(const Velocity& velocity) const {
  // Argument validation happens in the -= function call.
  Velocity result(*this);
  result -= velocity;
  return result;
}

Velocity& Velocity::operator*=(const double scalar) {
  this->data_ = this->data_ * scalar;
  return *this;
}

// Non-member multiplication functions
Velocity operator*(Velocity velocity, const double scalar) {
  return velocity *= scalar;
}

Velocity operator*(const double scalar, Velocity velocity) {
  return velocity *= scalar;
}

bool operator==(const Velocity& velocity1, const Velocity& velocity2) {
  // Two velocities are equal if they are of the same size and their data
  // values are equal.
  if (velocity1.size_ == velocity2.size_) {
    if (velocity1.data_.isApprox(velocity2.data_, 1e-6)) {
      return true;
    }
  }
  return false;
}

bool operator!=(const Velocity& velocity1, const Velocity& velocity2) {
  return !(velocity1 == velocity2);
}

double& Velocity::operator()(const int index) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Velocity index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Velocity object is empty");
  return data_(index);
}

const double& Velocity::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Velocity index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Velocity object is empty");
  return data_(index);
}

ostream& operator<<(ostream& os, const Velocity& velocity) {
  os << "Velocity[" << velocity.get_data().transpose() << "]";
  return os;
}

string Velocity::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

bool Velocity::IsEmpty() const { return size_ == 0; }

int Velocity::get_size() const { return size_; }

const VectorXd& Velocity::get_data() const {
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Velocity object is empty");
  return data_;
}

void Velocity::set_data(const VectorXd& data) {
  MORPH_REQUIRE(data.size() == size_, std::invalid_argument,
                "Velocity data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Velocity object is empty");
  data_ = data;
}

void Velocity::set_data(initializer_list<double> elements) {
  MORPH_REQUIRE((int)elements.size() == size_, std::invalid_argument,
                "Velocity data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Velocity object is empty");
  vector<double> data_vector(elements);
  data_ = Map<VectorXd>(&data_vector[0], size_);
}

Velocity Velocity::CreateLike(const Velocity& velocity) {
  Velocity new_velocity(velocity.get_size());
  return new_velocity;
}

}  // namespace constructs
}  // namespace morphac

