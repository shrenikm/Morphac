#include "constructs/include/coordinate2D.h"

namespace morphac {
namespace constructs {

template <typename T>
Coordinate2D<T>::Coordinate2D(T x, T y) : x_(x), y_(y) {}

template <typename T>
Coordinate2D<T>& Coordinate2D<T>::operator+=(const Coordinate2D& coord) {
  this->x_ += coord.x_;
  this->y_ += coord.y_;
  return *this;
}

template <typename T>
Coordinate2D<T> Coordinate2D<T>::operator+(const Coordinate2D& coord) const {
  Coordinate2D result;
  result.x_ = this->x_ + coord.x_;
  result.y_ = this->y_ + coord.y_;
  return result;
}

template <typename T>
Coordinate2D<T>& Coordinate2D<T>::operator-=(const Coordinate2D& coord) {
  this->x_ -= coord.x_;
  this->y_ -= coord.y_;
  return *this;
}

template <typename T>
Coordinate2D<T> Coordinate2D<T>::operator-(const Coordinate2D& coord) const {
  Coordinate2D result;
  result.x_ = this->x_ - coord.x_;
  result.y_ = this->y_ - coord.y_;
  return result;
}

template <typename T>
Coordinate2D<T> Coordinate2D<T>::operator*=(const T scalar) {
  this->x_ *= scalar;
  this->y_ *= scalar;
  return *this;
}

template <typename T>
Coordinate2D<T> operator*(Coordinate2D<T> coord, const T scalar) {
  return coord *= scalar;
}

template <typename T>
Coordinate2D<T> operator*(const T scalar, Coordinate2D<T> coord) {
  return coord *= scalar;
}

template <typename T>
T& Coordinate2D<T>::operator()(const int index) {
  MORPH_REQUIRE(index >= 0 && index < 2, std::out_of_range,
                "Coordinate2D index out of bounds.");
  if (index == 0) {
    return this->x_;
  } else {
    return this->y_;
  }
}

template <typename T>
T Coordinate2D<T>::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < 2, std::out_of_range,
                "Coordinate2D index out of bounds.");
  if (index == 0) {
    return this->x_;
  } else {
    return this->y_;
  }
}

template <typename T>
bool Coordinate2D<T>::operator==(const Coordinate2D& coord) {
  return (this->x_ == coord.x_) && (this->y_ == coord.y_);
}

template <typename T>
bool Coordinate2D<T>::operator!=(const Coordinate2D& coord) {
  return !(*this == coord);
}

template <typename T>
bool Coordinate2D<T>::operator<(const Coordinate2D& coord) {
  if ((this->x_ < coord.x_) ||
      ((this->x_ == coord.x_) && (this->y_ < coord.y_))) {
    return true;
  }
  return false;
}

template <typename T>
bool Coordinate2D<T>::operator>(const Coordinate2D& coord) {
  if ((this->x_ > coord.x_) ||
      ((this->x_ == coord.x_) && (this->y_ > coord.y_))) {
    return true;
  }
  return false;
}

template <typename T>
bool Coordinate2D<T>::operator<=(const Coordinate2D& coord) {
  return (*this == coord) || (*this < coord);
}

template <typename T>
bool Coordinate2D<T>::operator>=(const Coordinate2D& coord) {
  return (*this == coord) || (*this > coord);
}

template <typename T>
T Coordinate2D<T>::get_x() const {
  return x_;
}

template <typename T>
T Coordinate2D<T>::get_y() const {
  return y_;
}

template <typename T>
void Coordinate2D<T>::set_x(T x) {
  x_ = x;
}

template <typename T>
void Coordinate2D<T>::set_y(T y) {
  y_ = y;
}

template <typename T>
void Coordinate2D<T>::set_coordinate(T x, T y) {
  x_ = x;
  y_ = y;
}

// Template instantiations
template class Coordinate2D<int>;
template Coordinate2D<int> operator*(const int, Coordinate2D<int>);
template Coordinate2D<int> operator*(Coordinate2D<int>, const int);

template class Coordinate2D<double>;
template Coordinate2D<double> operator*(const double, Coordinate2D<double>);
template Coordinate2D<double> operator*(Coordinate2D<double>, const double);

}  // namespace constructs
}  // namespace morphac

