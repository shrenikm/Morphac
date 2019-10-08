#include "constructs/include/pose.h"

namespace morphac {
namespace constructs {

using Eigen::VectorXd;

Pose::Pose(int size) : size_(size), pose_(VectorXd::Zero(size)) {
  MORPH_REQUIRE(size > 0, std::invalid_argument, "Pose size is non-positive.");
}

Pose::Pose(VectorXd pose) : size_(pose.size()), pose_(pose) {
  MORPH_REQUIRE(pose.size() > 0, std::invalid_argument,
                "Pose size is non-positive.");
}

Pose::Pose(const Pose& pose) : size_(pose.size_), pose_(pose.pose_) {}

const int Pose::get_size() const { return size_; }

const VectorXd& Pose::get_pose() const { return pose_; }

double Pose::get_pose(int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Pose index out of bounds.");
  return pose_(index);
}

void Pose::set_pose(const VectorXd& pose) {
  MORPH_REQUIRE(pose.size() == size_, std::invalid_argument,
                "Pose and vector sizes do not match.");
  pose_ = pose;
}

void Pose::set_pose(int index, double pose_element) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Pose index out of bounds.");
  pose_(index) = pose_element;
}

}  // namespace constructs
}  // namespace morphac

