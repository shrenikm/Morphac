#include "constructs/include/pose.h"

namespace morphac {
namespace constructs {

using std::initializer_list;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

using Eigen::Map;
using Eigen::VectorXd;

Pose::Pose(const int size) : size_(size) {
  MORPH_REQUIRE(size >= 0, std::invalid_argument, "Pose size is non-positive.");
  data_ = VectorXd::Zero(size);
}

Pose::Pose(const VectorXd& data)
    : size_(data.size()), data_(data) {
  MORPH_REQUIRE(data.size() >= 0, std::invalid_argument,
                "Pose data size is non-positive.");
}

Pose::Pose(initializer_list<double> elements)
    : size_(elements.size()) {
  // As it is an initializer list, the size is always going to be >= 0 and need
  // not be checked.
  vector<double> data_vector(elements);
  data_ = Map<VectorXd>(&data_vector[0], size_);
}

Pose& Pose::operator+=(const Pose& pose) {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The += operator requires them "
                "to be of the "
                "same size.");
  this->data_ += pose.data_;
  return *this;
}

Pose Pose::operator+(const Pose& pose) const {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The + operator requires them "
                "to be of the "
                "same size.");
  Pose result(this->size_);
  result.data_ = this->data_ + pose.data_;
  return result;
}

Pose& Pose::operator-=(const Pose& pose) {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The -= operator requires them "
                "to be of the "
                "same size.");
  this->data_ -= pose.data_;
  return *this;
}

Pose Pose::operator-(const Pose& pose) const {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The - operator requires them "
                "to be of the "
                "same size.");
  Pose result(this->size_);
  result.data_ = this->data_ - pose.data_;
  return result;
}

Pose& Pose::operator*=(const double scalar) {
  this->data_ = this->data_ * scalar;
  return *this;
}

// Non-member multiplication functions
Pose operator*(Pose pose, const double scalar) { return pose *= scalar; }

Pose operator*(const double scalar, Pose pose) { return pose *= scalar; }

bool operator==(const Pose& pose1, const Pose& pose2) {
  // Two poses are equal if they are of the same size and their data values
  // are equal.
  if (pose1.size_ == pose2.size_) {
    if (pose1.data_.isApprox(pose2.data_, 1e-6)) {
      return true;
    }
  }
  return false;
}

bool operator!=(const Pose& pose1, const Pose& pose2) {
  return !(pose1 == pose2);
}

double& Pose::operator()(const int index) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Pose index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  return data_(index);
}

double Pose::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Pose index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  return data_(index);
}

ostream& operator<<(ostream& os, const Pose& pose) {
  os << "Pose[" << pose.get_data().transpose() << "]";
  return os;
}

string Pose::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

bool Pose::IsEmpty() const { return size_ == 0; }

int Pose::get_size() const { return size_; }

const VectorXd& Pose::get_data() const {
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  return data_;
}

void Pose::set_data(const VectorXd& data) {
  MORPH_REQUIRE(data.size() == size_, std::invalid_argument,
                "Pose data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  data_ = data;
}

void Pose::set_data(initializer_list<double> elements) {
  MORPH_REQUIRE((int)elements.size() == size_, std::invalid_argument,
                "Pose data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  vector<double> data_vector(elements);
  data_ = Map<VectorXd>(&data_vector[0], size_);
}

Pose Pose::CreateLike(const Pose& pose) {
  Pose new_pose(pose.get_size());
  return new_pose;
}

}  // namespace constructs
}  // namespace morphac

