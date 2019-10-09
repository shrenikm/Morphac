#ifndef COORDINATE_H
#define COORDINATE_H

namespace morphac {
namespace constructs {

template <typename T>
class Coordinate2D {
 public:
  Coordinate2D(T x = 0, T y = 0);
  Coordinate2D(const Coordinate2D& coord);

  Coordinate2D& operator+=(const Coordinate2D& coord);
  Coordinate2D operator+(const Coordinate2D& coord);
  Coordinate2D& operator-=(const Coordinate2D& coord);
  Coordinate2D operator-(const Coordinate2D& coord);
  bool operator==(const Coordinate2D& coord);
  bool operator!=(const Coordinate2D& coord);
  bool operator<(const Coordinate2D& coord);
  bool operator>(const Coordinate2D& coord);
  bool operator<=(const Coordinate2D& coord);
  bool operator>=(const Coordinate2D& coord);

  T get_x() const;
  T get_y() const;
  void set_x(T x);
  void set_y(T y);
  void set_coordinate(T x, T y);

 private:
  T x_;
  T y_;
};

}  // namespace constructs
}  // namespace morphac

#endif
