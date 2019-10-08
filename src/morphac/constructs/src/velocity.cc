#include "constructs/include/velocity.h"

namespace morphac {
namespace constructs {

using Eigen::VectorXd;

Velocity::Velocity(int size) : size_(size), velocity_(VectorXd::Zero(size)) {
  MORPH_REQUIRE(size > 0, std::invalid_argument,
                "Velocity size is non-positive.");
}

Velocity::Velocity(VectorXd velocity)
    : size_(velocity.size()), velocity_(velocity) {
  MORPH_REQUIRE(velocity.size() > 0, std::invalid_argument,
                "Velocity size is non-positive.");
}

Velocity::Velocity(const Velocity& velocity)
    : size_(velocity.size_), velocity_(velocity.velocity_) {}

const int Velocity::get_size() const { return size_; }

const VectorXd& Velocity::get_velocity() const { return velocity_; }

double Velocity::get_velocity(int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Velocity index out of bounds.");
  return velocity_(index);
}

void Velocity::set_velocity(const VectorXd& velocity) {
  MORPH_REQUIRE(velocity.size() == size_, std::invalid_argument,
                "Velocity and vector sizes do not match.");
  velocity_ = velocity;
}

void Velocity::set_velocity(int index, double velocity_element) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Velocity index out of bounds.");
  velocity_(index) = velocity_element;
}

}  // namespace constructs
}  // namespace morphac

