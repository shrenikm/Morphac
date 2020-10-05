#ifndef COORDINATE_H
#define COORDINATE_H

#include <sstream>

#include "Eigen/Dense"
#include "common/aliases/include/eigen_aliases.h"
#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class Coordinate {
 public:
  Coordinate(const double x = 0, const double y = 0);
  Coordinate(const morphac::common::aliases::Point& data);

  // Copy constructor.
  Coordinate(const Coordinate& coord) = default;

  // Copy assignment.
  Coordinate& operator=(const Coordinate& coord) = default;

  Coordinate& operator+=(const Coordinate& coord);
  Coordinate operator+(const Coordinate& coord) const;
  Coordinate& operator-=(const Coordinate& coord);
  Coordinate operator-(const Coordinate& coord) const;
  Coordinate operator*=(const double scalar);

  double& operator[](const int index);
  const double& operator[](const int index) const;

  bool operator==(const Coordinate& coord) const;
  bool operator!=(const Coordinate& coord) const;
  bool operator<(const Coordinate& coord) const;
  bool operator>(const Coordinate& coord) const;
  bool operator<=(const Coordinate& coord) const;
  bool operator>=(const Coordinate& coord) const;

  friend std::ostream& operator<<(std::ostream& os, const Coordinate& coord);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  double get_x() const;
  double get_y() const;
  const morphac::common::aliases::Point get_data() const;
  void set_x(const double x);
  void set_y(const double y);
  void set_xy(const double x, const double y);
  void set_data(const morphac::common::aliases::Point& data);

 private:
  double x_;
  double y_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
Coordinate operator*(Coordinate coord, const double scalar);
Coordinate operator*(const double scalar, Coordinate coord);

}  // namespace constructs
}  // namespace morphac

#endif
