#ifndef COORDINATE_H
#define COORDINATE_H

namespace morphac {
namespace constructs {

class Coordinate2D {
 public:
  Coordinate2D(int x = 0, int y = 0);
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

  int get_x() const;
  int get_y() const;
  void set_x(int x);
  void set_y(int y);
  void set_coordinate(int x, int y);

 private:
  int x_;
  int y_;
};

}  // namespace constructs
}  // namespace morphac

#endif
