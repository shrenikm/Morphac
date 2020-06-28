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
  pose_data_ = VectorXd::Zero(size);
}

Pose::Pose(const VectorXd& pose_data)
    : size_(pose_data.size()), pose_data_(pose_data) {
  MORPH_REQUIRE(pose_data.size() >= 0, std::invalid_argument,
                "Pose data size is non-positive.");
}

Pose::Pose(initializer_list<double> pose_elements)
    : size_(pose_elements.size()) {
  // As it is an initializer list, the size is always going to be >= 0 and need
  // not be checked.
  vector<double> pose_data_vector(pose_elements);
  pose_data_ = Map<VectorXd>(&pose_data_vector[0], size_);
}

Pose& Pose::operator+=(const Pose& pose) {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The += operator requires them "
                "to be of the "
                "same size.");
  this->pose_data_ += pose.pose_data_;
  return *this;
}

Pose Pose::operator+(const Pose& pose) const {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The + operator requires them "
                "to be of the "
                "same size.");
  Pose result(this->size_);
  result.pose_data_ = this->pose_data_ + pose.pose_data_;
  return result;
}

Pose& Pose::operator-=(const Pose& pose) {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The -= operator requires them "
                "to be of the "
                "same size.");
  this->pose_data_ -= pose.pose_data_;
  return *this;
}

Pose Pose::operator-(const Pose& pose) const {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The - operator requires them "
                "to be of the "
                "same size.");
  Pose result(this->size_);
  result.pose_data_ = this->pose_data_ - pose.pose_data_;
  return result;
}

Pose& Pose::operator*=(const double scalar) {
  this->pose_data_ = this->pose_data_ * scalar;
  return *this;
}

// Non-member multiplication functions
Pose operator*(Pose pose, const double scalar) { return pose *= scalar; }

Pose operator*(const double scalar, Pose pose) { return pose *= scalar; }

bool operator==(const Pose& pose1, const Pose& pose2) {
  // Two poses are equal if they are of the same size and their data values
  // are equal.
  if (pose1.size_ == pose2.size_) {
    if (pose1.pose_data_.isApprox(pose2.pose_data_, 1e-6)) {
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
  return pose_data_(index);
}

double Pose::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Pose index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  return pose_data_(index);
}

ostream& operator<<(ostream& os, const Pose& pose) {
  os << "Pose[" << pose.get_pose_data().transpose() << "]";
  return os;
}

string Pose::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

bool Pose::IsEmpty() const { return size_ == 0; }

int Pose::get_size() const { return size_; }

const VectorXd& Pose::get_pose_data() const {
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  return pose_data_;
}

void Pose::set_pose_data(const VectorXd& pose_data) {
  MORPH_REQUIRE(pose_data.size() == size_, std::invalid_argument,
                "Pose data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  pose_data_ = pose_data;
}

void Pose::set_pose_data(initializer_list<double> pose_elements) {
  MORPH_REQUIRE((int)pose_elements.size() == size_, std::invalid_argument,
                "Pose data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  vector<double> pose_data_vector(pose_elements);
  pose_data_ = Map<VectorXd>(&pose_data_vector[0], size_);
}

Pose Pose::CreateLike(const Pose& pose) {
  Pose new_pose(pose.get_size());
  return new_pose;
}

}  // namespace constructs
}  // namespace morphac

