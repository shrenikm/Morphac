#include "constructs/include/velocity.h"

namespace morphac {
namespace constructs {

using Eigen::VectorXd;

Velocity::Velocity(int size) : size_(size) {
  MORPH_REQUIRE(size > 0, std::invalid_argument,
                "Velocity size is non-positive.");
  velocity_ = VectorXd::Zero(size);
}

Velocity::Velocity(VectorXd velocity) {
  MORPH_REQUIRE(velocity.size() > 0, std::invalid_argument,
                "Velocity size is non-positive.");
  size_ = velocity.size();
  velocity_ = velocity;
}

Velocity::Velocity(const Velocity& velocity) {
  this->size_ = velocity.size_;
  this->velocity_ = velocity.velocity_;
}

int Velocity::get_size() { return size_; }

VectorXd Velocity::get_velocity() { return velocity_; }

double Velocity::get_velocity(int index) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Velocity index out of bounds.");
  return velocity_(index);
}

void Velocity::set_velocity(VectorXd velocity) {
  MORPH_REQUIRE(velocity.size() > 0, std::invalid_argument,
                "Velocity size is non-positive.");
  size_ = velocity.size();
  velocity_ = velocity;
}

void Velocity::set_velocity(int index, double velocity_element) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Velocity index out of bounds.");
  velocity_(index) = velocity_element;
}

}  // namespace constructs
}  // namespace morphac

