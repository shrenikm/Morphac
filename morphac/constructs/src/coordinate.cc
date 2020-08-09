#include "constructs/include/coordinate.h"

namespace morphac {
namespace constructs {

using std::ostream;
using std::ostringstream;
using std::string;
using Eigen::Matrix;

template <typename T>
Coordinate<T>::Coordinate(const T x, const T y) : x_(x), y_(y) {}

template <typename T>
Coordinate<T>::Coordinate(const Coordinate<T>& coord)
    : x_(coord.x_), y_(coord.y_) {}

template <typename T>
Coordinate<T>& Coordinate<T>::operator+=(const Coordinate& coord) {
  this->x_ += coord.x_;
  this->y_ += coord.y_;
  return *this;
}

template <typename T>
Coordinate<T> Coordinate<T>::operator+(const Coordinate& coord) const {
  Coordinate result;
  result.x_ = this->x_ + coord.x_;
  result.y_ = this->y_ + coord.y_;
  return result;
}

template <typename T>
Coordinate<T>& Coordinate<T>::operator-=(const Coordinate& coord) {
  this->x_ -= coord.x_;
  this->y_ -= coord.y_;
  return *this;
}

template <typename T>
Coordinate<T> Coordinate<T>::operator-(const Coordinate& coord) const {
  Coordinate result;
  result.x_ = this->x_ - coord.x_;
  result.y_ = this->y_ - coord.y_;
  return result;
}

template <typename T>
Coordinate<T> Coordinate<T>::operator*=(const T scalar) {
  this->x_ *= scalar;
  this->y_ *= scalar;
  return *this;
}

template <typename T>
Coordinate<T> operator*(Coordinate<T> coord, const T scalar) {
  return coord *= scalar;
}

template <typename T>
Coordinate<T> operator*(const T scalar, Coordinate<T> coord) {
  return coord *= scalar;
}

template <typename T>
T& Coordinate<T>::operator[](const int index) {
  MORPH_REQUIRE(index >= 0 && index < 2, std::out_of_range,
                "Coordinate index out of bounds.");
  if (index == 0) {
    return this->x_;
  } else {
    return this->y_;
  }
}

template <typename T>
T Coordinate<T>::operator[](const int index) const {
  MORPH_REQUIRE(index >= 0 && index < 2, std::out_of_range,
                "Coordinate index out of bounds.");
  if (index == 0) {
    return this->x_;
  } else {
    return this->y_;
  }
}

template <typename T>
bool Coordinate<T>::operator==(const Coordinate& coord) const {
  return (this->x_ == coord.x_) && (this->y_ == coord.y_);
}

template <typename T>
bool Coordinate<T>::operator!=(const Coordinate& coord) const {
  return !(*this == coord);
}

template <typename T>
bool Coordinate<T>::operator<(const Coordinate& coord) const {
  if ((this->x_ < coord.x_) ||
      ((this->x_ == coord.x_) && (this->y_ < coord.y_))) {
    return true;
  }
  return false;
}

template <typename T>
bool Coordinate<T>::operator>(const Coordinate& coord) const {
  if ((this->x_ > coord.x_) ||
      ((this->x_ == coord.x_) && (this->y_ > coord.y_))) {
    return true;
  }
  return false;
}

template <typename T>
bool Coordinate<T>::operator<=(const Coordinate& coord) const {
  return (*this == coord) || (*this < coord);
}

template <typename T>
bool Coordinate<T>::operator>=(const Coordinate& coord) const {
  return (*this == coord) || (*this > coord);
}

template <typename T>
ostream& operator<<(ostream& os, const Coordinate<T>& coord) {
  os << "Coordinate[" << coord.get_x() << ", " << coord.get_y() << "]";
  return os;
}

template <typename T>
string Coordinate<T>::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

template <typename T>
T Coordinate<T>::get_x() const {
  return x_;
}

template <typename T>
T Coordinate<T>::get_y() const {
  return y_;
}

template <typename T>
const Matrix<T, 2, 1> Coordinate<T>::get_data() const {
  Matrix<T, 2, 1> data(2);
  data << this->get_x(), this->get_y();
  return data;
}

template <typename T>
void Coordinate<T>::set_x(const T x) {
  x_ = x;
}

template <typename T>
void Coordinate<T>::set_y(const T y) {
  y_ = y;
}

template <typename T>
void Coordinate<T>::set_xy(const T x, const T y) {
  x_ = x;
  y_ = y;
}

template <typename T>
void Coordinate<T>::set_data(const Matrix<T, 2, 1>& data) {
  MORPH_REQUIRE(data.size() == 2, std::invalid_argument,
                "Coordinate data must be of size 2.");
  this->set_x(data(0));
  this->set_y(data(1));
}

// Template instantiations
template class Coordinate<int>;
template Coordinate<int> operator*(const int, Coordinate<int>);
template Coordinate<int> operator*(Coordinate<int>, const int);

template class Coordinate<double>;
template Coordinate<double> operator*(const double, Coordinate<double>);
template Coordinate<double> operator*(Coordinate<double>, const double);

}  // namespace constructs
}  // namespace morphac

