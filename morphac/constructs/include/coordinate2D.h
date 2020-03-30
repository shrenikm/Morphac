#ifndef COORDINATE_H
#define COORDINATE_H

#include <sstream>

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

template <typename T>
class Coordinate2D {
 public:
  Coordinate2D(const T x = 0, const T y = 0);

  Coordinate2D& operator+=(const Coordinate2D& coord);
  Coordinate2D operator+(const Coordinate2D& coord) const;
  Coordinate2D& operator-=(const Coordinate2D& coord);
  Coordinate2D operator-(const Coordinate2D& coord) const;
  Coordinate2D operator*=(const T scalar);

  T& operator()(const int index);
  T operator()(const int index) const;

  bool operator==(const Coordinate2D& coord) const;
  bool operator!=(const Coordinate2D& coord) const;
  bool operator<(const Coordinate2D& coord) const;
  bool operator>(const Coordinate2D& coord) const;
  bool operator<=(const Coordinate2D& coord) const;
  bool operator>=(const Coordinate2D& coord) const;

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const Coordinate2D<U>& coord);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  T get_x() const;
  T get_y() const;
  const Eigen::Matrix<T, 2, 1> get_coordinate_vector() const;
  void set_x(const T x);
  void set_y(const T y);
  void set_coordinate(const T x, const T y);
  void set_coordinate_vector(
      const Eigen::Matrix<T, 2, 1>& coord_vector);

 private:
  T x_;
  T y_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
template <typename T>
Coordinate2D<T> operator*(Coordinate2D<T> coord, const T scalar);

template <typename T>
Coordinate2D<T> operator*(const T scalar, Coordinate2D<T> coord);

}  // namespace constructs
}  // namespace morphac

#endif