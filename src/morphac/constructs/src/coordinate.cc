#include "constructs/include/coordinate.h"

namespace morphac {
namespace constructs {

Coordinate2D::Coordinate2D(int x, int y) : x_(x), y_(y) {}

Coordinate2D::Coordinate2D(const Coordinate2D& coord) {
  this->x_ = coord.x_;
  this->y_ = coord.y_;
}

Coordinate2D& Coordinate2D::operator+=(const Coordinate2D& coord) {
  this->x_ += coord.x_;
  this->y_ += coord.y_;
  return *this;
}

Coordinate2D Coordinate2D::operator+(const Coordinate2D& coord) {
  Coordinate2D result;
  result.x_ = this->x_ + coord.x_;
  result.y_ = this->y_ + coord.y_;
  return result;
}

Coordinate2D& Coordinate2D::operator-=(const Coordinate2D& coord) {
  this->x_ -= coord.x_;
  this->y_ -= coord.y_;
  return *this;
}

Coordinate2D Coordinate2D::operator-(const Coordinate2D& coord) {
  Coordinate2D result;
  result.x_ = this->x_ - coord.x_;
  result.y_ = this->y_ - coord.y_;
  return result;
}

bool Coordinate2D::operator==(const Coordinate2D& coord) {
  return (this->x_ == coord.x_) && (this->y_ == coord.y_);
}

bool Coordinate2D::operator!=(const Coordinate2D& coord) {
  return !(*this == coord);
}

bool Coordinate2D::operator<(const Coordinate2D& coord) {
  if ((this->x_ < coord.x_) ||
      ((this->x_ == coord.x_) && (this->y_ < coord.y_))) {
    return true;
  }
  return false;
}

bool Coordinate2D::operator>(const Coordinate2D& coord) {
  if ((this->x_ > coord.x_) ||
      ((this->x_ == coord.x_) && (this->y_ > coord.y_))) {
    return true;
  }
  return false;
}

bool Coordinate2D::operator<=(const Coordinate2D& coord) {
  return (*this == coord) || (*this < coord);
}

bool Coordinate2D::operator>=(const Coordinate2D& coord) {
  return (*this == coord) || (*this > coord);
}

int Coordinate2D::get_x() { return x_; }

int Coordinate2D::get_y() { return y_; }

void Coordinate2D::set_x(int x) { x_ = x; }

void Coordinate2D::set_y(int y) { y_ = y; }

void Coordinate2D::set_coordinate(int x, int y) {
  x_ = x;
  y_ = y;
}

}  // namespace constructs
}  // namespace morphac
