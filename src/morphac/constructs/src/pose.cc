#include "constructs/include/pose.h"

namespace morphac {
namespace constructs {

using Eigen::VectorXd;

Pose::Pose(int size) : size_(size) {
  MORPH_REQUIRE(size > 0, std::invalid_argument, "Pose size is non-positive.");
  pose_vector_ = VectorXd::Zero(size);
}

Pose::Pose(VectorXd pose_vector)
    : size_(pose_vector.size()), pose_vector_(pose_vector) {
  MORPH_REQUIRE(pose_vector.size() > 0, std::invalid_argument,
                "Pose vector size is non-positive.");
}

const int Pose::get_size() const { return size_; }

const VectorXd& Pose::get_pose_vector() const { return pose_vector_; }

double Pose::get_pose_at(int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Pose index out of bounds.");
  return pose_vector_(index);
}

void Pose::set_pose_vector(const VectorXd& pose_vector) {
  MORPH_REQUIRE(pose_vector.size() == size_, std::invalid_argument,
                "Pose vector size is incorrect.");
  pose_vector_ = pose_vector;
}

void Pose::set_pose_at(int index, double pose_element) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Pose index out of bounds.");
  pose_vector_(index) = pose_element;
}

}  // namespace constructs
}  // namespace morphac

