#include "constructs/include/velocity.h"

namespace morphac {
namespace constructs {

using Eigen::VectorXd;

Velocity::Velocity(int size) : size_(size) {
  MORPH_REQUIRE(size > 0, std::invalid_argument,
                "Velocity size is non-positive.");
  velocity_vector_ = VectorXd::Zero(size);
}

Velocity::Velocity(const VectorXd& velocity_vector)
    : size_(velocity_vector.size()), velocity_vector_(velocity_vector) {
  MORPH_REQUIRE(velocity_vector.size() > 0, std::invalid_argument,
                "Velocity vector size is non-positive.");
}

const int Velocity::get_size() const { return size_; }

const VectorXd& Velocity::get_velocity_vector() const {
  return velocity_vector_;
}

double Velocity::get_velocity_at(int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Velocity index out of bounds.");
  return velocity_vector_(index);
}

void Velocity::set_velocity_vector(const VectorXd& velocity_vector) {
  MORPH_REQUIRE(velocity_vector.size() == size_, std::invalid_argument,
                "Velocity vector size is incorrect.");
  velocity_vector_ = velocity_vector;
}

void Velocity::set_velocity_at(int index, double velocity_element) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Velocity index out of bounds.");
  velocity_vector_(index) = velocity_element;
}

}  // namespace constructs
}  // namespace morphac

