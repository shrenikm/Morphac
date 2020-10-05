#include "constructs/include/coordinate.h"

namespace morphac {
namespace constructs {

using morphac::common::aliases::Point;
using std::ostream;
using std::ostringstream;
using std::string;

Coordinate::Coordinate(const double x, const double y) : x_(x), y_(y) {}

Coordinate::Coordinate(const Point& data) : x_(data(0)), y_(data(1)) {}

Coordinate& Coordinate::operator+=(const Coordinate& coord) {
  this->x_ += coord.x_;
  this->y_ += coord.y_;
  return *this;
}

Coordinate Coordinate::operator+(const Coordinate& coord) const {
  Coordinate result;
  result.x_ = this->x_ + coord.x_;
  result.y_ = this->y_ + coord.y_;
  return result;
}

Coordinate& Coordinate::operator-=(const Coordinate& coord) {
  this->x_ -= coord.x_;
  this->y_ -= coord.y_;
  return *this;
}

Coordinate Coordinate::operator-(const Coordinate& coord) const {
  Coordinate result;
  result.x_ = this->x_ - coord.x_;
  result.y_ = this->y_ - coord.y_;
  return result;
}

Coordinate Coordinate::operator*=(const double scalar) {
  this->x_ *= scalar;
  this->y_ *= scalar;
  return *this;
}

Coordinate operator*(Coordinate coord, const double scalar) {
  return coord *= scalar;
}

Coordinate operator*(const double scalar, Coordinate coord) {
  return coord *= scalar;
}

double& Coordinate::operator[](const int index) {
  MORPH_REQUIRE(index >= 0 && index < 2, std::out_of_range,
                "Coordinate index out of bounds.");
  if (index == 0) {
    return this->x_;
  } else {
    return this->y_;
  }
}

const double& Coordinate::operator[](const int index) const {
  MORPH_REQUIRE(index >= 0 && index < 2, std::out_of_range,
                "Coordinate index out of bounds.");
  if (index == 0) {
    return this->x_;
  } else {
    return this->y_;
  }
}

bool Coordinate::operator==(const Coordinate& coord) const {
  return (this->x_ == coord.x_) && (this->y_ == coord.y_);
}

bool Coordinate::operator!=(const Coordinate& coord) const {
  return !(*this == coord);
}

bool Coordinate::operator<(const Coordinate& coord) const {
  if ((this->x_ < coord.x_) ||
      ((this->x_ == coord.x_) && (this->y_ < coord.y_))) {
    return true;
  }
  return false;
}

bool Coordinate::operator>(const Coordinate& coord) const {
  if ((this->x_ > coord.x_) ||
      ((this->x_ == coord.x_) && (this->y_ > coord.y_))) {
    return true;
  }
  return false;
}

bool Coordinate::operator<=(const Coordinate& coord) const {
  return (*this == coord) || (*this < coord);
}

bool Coordinate::operator>=(const Coordinate& coord) const {
  return (*this == coord) || (*this > coord);
}

ostream& operator<<(ostream& os, const Coordinate& coord) {
  os << "Coordinate[" << coord.get_x() << ", " << coord.get_y() << "]";
  return os;
}

string Coordinate::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

double Coordinate::get_x() const { return x_; }

double Coordinate::get_y() const { return y_; }

const Point Coordinate::get_data() const {
  Point data(2);
  data << this->get_x(), this->get_y();
  return data;
}

void Coordinate::set_x(const double x) { x_ = x; }

void Coordinate::set_y(const double y) { y_ = y; }

void Coordinate::set_xy(const double x, const double y) {
  x_ = x;
  y_ = y;
}

void Coordinate::set_data(const Point& data) {
  MORPH_REQUIRE(data.size() == 2, std::invalid_argument,
                "Coordinate data must be of size 2.");
  this->set_x(data(0));
  this->set_y(data(1));
}

}  // namespace constructs
}  // namespace morphac
