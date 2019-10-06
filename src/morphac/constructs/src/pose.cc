#include "constructs/include/pose.h"

namespace morphac {
namespace constructs {

using Eigen::VectorXd;

Pose::Pose(int size) : size_(size) {
  MORPH_REQUIRE(size > 0, "Pose size is non-positive.", std::invalid_argument);
  pose_ = VectorXd::Zero(size);
}

Pose::Pose(VectorXd pose) {
  MORPH_REQUIRE(pose.size() > 0, "Pose size is non-positive.",
                std::invalid_argument);
  size_ = pose.size();
  pose_ = pose;
}

Pose::Pose(const Pose& pose) {
  this->size_ = pose.size_;
  this->pose_ = pose.pose_;
}

int Pose::get_size() { return size_; }

VectorXd Pose::get_pose() { return pose_; }

double Pose::get_pose(int index) {
  MORPH_REQUIRE(index >= 0 && index < size_, "Pose index out of bounds.",
                std::out_of_range);
  return pose_(index);
}

void Pose::set_pose(VectorXd pose) {
  MORPH_REQUIRE(pose.size() > 0, "Pose size is non-positive.",
                std::invalid_argument);
  size_ = pose.size();
  pose_ = pose;
}

void Pose::set_pose(int index, double pose_element) {
  MORPH_REQUIRE(index >= 0 && index < size_, "Pose index out of bounds.",
                std::out_of_range);
  pose_(index) = pose_element;
}

}  // namespace constructs
}  // namespace morphac

