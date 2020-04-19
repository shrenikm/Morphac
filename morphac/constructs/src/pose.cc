#include "constructs/include/pose.h"

namespace morphac {
namespace constructs {

using std::initializer_list;
using std::ostream;
using std::ostringstream;
using std::string;

using Eigen::Map;
using Eigen::VectorXd;

Pose::Pose(const int size) : size_(size) {
  MORPH_REQUIRE(size >= 0, std::invalid_argument, "Pose size is non-positive.");
  pose_vector_ = VectorXd::Zero(size);
}

Pose::Pose(const VectorXd& pose_vector)
    : size_(pose_vector.size()), pose_vector_(pose_vector) {
  MORPH_REQUIRE(pose_vector.size() >= 0, std::invalid_argument,
                "Pose vector size is non-positive.");
}

Pose::Pose(initializer_list<double> pose_elements)
    : size_(pose_elements.size()) {
  // As it is an initializer list, the size is always going to be >= 0.
  std::vector<double> data(pose_elements);
  pose_vector_ = Map<VectorXd>(&data[0], size_);
}

Pose& Pose::operator+=(const Pose& pose) {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The += operator requires them "
                "to be of the "
                "same size.");
  this->pose_vector_ += pose.pose_vector_;
  return *this;
}

Pose Pose::operator+(const Pose& pose) const {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The + operator requires them "
                "to be of the "
                "same size.");
  Pose result(this->size_);
  result.pose_vector_ = this->pose_vector_ + pose.pose_vector_;
  return result;
}

Pose& Pose::operator-=(const Pose& pose) {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The -= operator requires them "
                "to be of the "
                "same size.");
  this->pose_vector_ -= pose.pose_vector_;
  return *this;
}

Pose Pose::operator-(const Pose& pose) const {
  MORPH_REQUIRE(this->size_ == pose.size_, std::invalid_argument,
                "Poses are not of the same size. The - operator requires them "
                "to be of the "
                "same size.");
  Pose result(this->size_);
  result.pose_vector_ = this->pose_vector_ - pose.pose_vector_;
  return result;
}

Pose& Pose::operator*=(const double scalar) {
  this->pose_vector_ = this->pose_vector_ * scalar;
  return *this;
}

// Non-member multiplication functions
Pose operator*(Pose pose, const double scalar) { return pose *= scalar; }

Pose operator*(const double scalar, Pose pose) { return pose *= scalar; }

double& Pose::operator()(const int index) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Pose index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  return pose_vector_(index);
}

double Pose::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Pose index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  return pose_vector_(index);
}

ostream& operator<<(ostream& os, const Pose& pose) {
  os << "Pose[" << pose.get_pose_vector().transpose() << "]";
  return os;
}

string Pose::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

bool Pose::IsEmpty() const { return size_ == 0; }

int Pose::get_size() const { return size_; }

const VectorXd& Pose::get_pose_vector() const {
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  return pose_vector_;
}

void Pose::set_pose_vector(const VectorXd& pose_vector) {
  MORPH_REQUIRE(pose_vector.size() == size_, std::invalid_argument,
                "Pose vector size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  pose_vector_ = pose_vector;
}

void Pose::set_pose_vector(initializer_list<double> pose_elements) {
  MORPH_REQUIRE(pose_elements.size() == size_, std::invalid_argument,
                "Pose vector size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "Pose object is empty");
  std::vector<double> data(pose_elements);
  pose_vector_ = Map<VectorXd>(&data[0], size_);
}

Pose Pose::CreateLike(const Pose& pose) {
  Pose new_pose(pose.get_size());
  return new_pose;
}

}  // namespace constructs
}  // namespace morphac

