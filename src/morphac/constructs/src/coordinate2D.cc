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

template class Coordinate2D<int>;
template class Coordinate2D<double>;

}  // namespace constructs
}  // namespace morphac

