#include "constructs/include/velocity.h"

namespace morphac {
namespace constructs {

using Eigen::VectorXd;

Velocity::Velocity(const int size) : size_(size) {
  MORPH_REQUIRE(size >= 0, std::invalid_argument,
                "Velocity size is non-positive.");
  velocity_vector_ = VectorXd::Zero(size);
}

Velocity::Velocity(const VectorXd& velocity_vector)
    : size_(velocity_vector.size()), velocity_vector_(velocity_vector) {
  MORPH_REQUIRE(velocity_vector.size() >= 0, std::invalid_argument,
                "Velocity vector size is non-positive.");
}

Velocity& Velocity::operator+=(const Velocity& velocity) {
  MORPH_REQUIRE(
      this->size_ == velocity.size_, std::invalid_argument,
      "Velocities are not of the same size. The += operator requires them "
      "to be of the "
      "same size.");
  this->velocity_vector_ += velocity.velocity_vector_;
  return *this;
}

Velocity Velocity::operator+(const Velocity& velocity) {
  MORPH_REQUIRE(
      this->size_ == velocity.size_, std::invalid_argument,
      "Velocities are not of the same size. The + operator requires them "
      "to be of the "
      "same size.");
  Velocity result(this->size_);
  result.velocity_vector_ = this->velocity_vector_ + velocity.velocity_vector_;
  return result;
}

Velocity& Velocity::operator-=(const Velocity& velocity) {
  MORPH_REQUIRE(
      this->size_ == velocity.size_, std::invalid_argument,
      "Velocities are not of the same size. The -= operator requires them "
      "to be of the "
      "same size.");
  this->velocity_vector_ -= velocity.velocity_vector_;
  return *this;
}

Velocity Velocity::operator-(const Velocity& velocity) {
  MORPH_REQUIRE(
      this->size_ == velocity.size_, std::invalid_argument,
      "Velocities are not of the same size. The - operator requires them "
      "to be of the "
      "same size.");
  Velocity result(this->size_);
  result.velocity_vector_ = this->velocity_vector_ - velocity.velocity_vector_;
  return result;
}

Velocity& Velocity::operator*=(const double scalar) {
  this->velocity_vector_ = this->velocity_vector_ * scalar;
  return *this;
}

// Non-member multiplication functions
Velocity operator*(Velocity velocity, const double scalar) {
  return velocity *= scalar;
}

Velocity operator*(const double scalar, Velocity velocity) {
  return velocity *= scalar;
}

bool Velocity::is_empty() const { return size_ == 0; }

const int Velocity::get_size() const { return size_; }

const VectorXd& Velocity::get_velocity_vector() const {
  MORPH_REQUIRE(!is_empty(), std::logic_error, "Velocity object is empty");
  return velocity_vector_;
}

double Velocity::get_velocity_at(int index) const {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Velocity index out of bounds.");
  MORPH_REQUIRE(!is_empty(), std::logic_error, "Velocity object is empty");
  return velocity_vector_(index);
}

void Velocity::set_velocity_vector(const VectorXd& velocity_vector) {
  MORPH_REQUIRE(velocity_vector.size() == size_, std::invalid_argument,
                "Velocity vector size is incorrect.");
  MORPH_REQUIRE(!is_empty(), std::logic_error, "Velocity object is empty");
  velocity_vector_ = velocity_vector;
}

void Velocity::set_velocity_at(int index, double velocity_element) {
  MORPH_REQUIRE(index >= 0 && index < size_, std::out_of_range,
                "Velocity index out of bounds.");
  MORPH_REQUIRE(!is_empty(), std::logic_error, "Velocity object is empty");
  velocity_vector_(index) = velocity_element;
}

}  // namespace constructs
}  // namespace morphac

