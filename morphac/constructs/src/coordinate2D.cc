#include "constructs/include/coordinate2D.h"

namespace morphac {
namespace constructs {

using std::ostream;
using std::ostringstream;
using std::string;
using Eigen::Matrix;

template <typename T>
Coordinate2D<T>::Coordinate2D(const T x, const T y) : x_(x), y_(y) {}

template <typename T>
Coordinate2D<T>::Coordinate2D(const Coordinate2D<T>& coord)
    : x_(coord.x_), y_(coord.y_) {}

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
bool Coordinate2D<T>::operator==(const Coordinate2D& coord) const {
  return (this->x_ == coord.x_) && (this->y_ == coord.y_);
}

template <typename T>
bool Coordinate2D<T>::operator!=(const Coordinate2D& coord) const {
  return !(*this == coord);
}

template <typename T>
bool Coordinate2D<T>::operator<(const Coordinate2D& coord) const {
  if ((this->x_ < coord.x_) ||
      ((this->x_ == coord.x_) && (this->y_ < coord.y_))) {
    return true;
  }
  return false;
}

template <typename T>
bool Coordinate2D<T>::operator>(const Coordinate2D& coord) const {
  if ((this->x_ > coord.x_) ||
      ((this->x_ == coord.x_) && (this->y_ > coord.y_))) {
    return true;
  }
  return false;
}

template <typename T>
bool Coordinate2D<T>::operator<=(const Coordinate2D& coord) const {
  return (*this == coord) || (*this < coord);
}

template <typename T>
bool Coordinate2D<T>::operator>=(const Coordinate2D& coord) const {
  return (*this == coord) || (*this > coord);
}

template <typename T>
ostream& operator<<(ostream& os, const Coordinate2D<T>& coord) {
  os << "Coordinate2D[" << coord.get_x() << ", " << coord.get_y() << "]";
  return os;
}

template <typename T>
string Coordinate2D<T>::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
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
const Matrix<T, 2, 1> Coordinate2D<T>::get_coordinate_vector() const {
  Matrix<T, 2, 1> coord_vector(2);
  coord_vector << this->get_x(), this->get_y();
  return coord_vector;
}

template <typename T>
void Coordinate2D<T>::set_x(const T x) {
  x_ = x;
}

template <typename T>
void Coordinate2D<T>::set_y(const T y) {
  y_ = y;
}

template <typename T>
void Coordinate2D<T>::set_coordinate(const T x, const T y) {
  x_ = x;
  y_ = y;
}

template <typename T>
void Coordinate2D<T>::set_coordinate_vector(
    const Matrix<T, 2, 1>& coord_vector) {
  MORPH_REQUIRE(coord_vector.size() == 2, std::invalid_argument,
                "Coordinate vector must be of size 2.");
  this->set_x(coord_vector(0));
  this->set_y(coord_vector(1));
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

