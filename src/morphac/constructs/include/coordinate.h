#ifndef COORDINATE_H
#define COORDINATE_H

namespace morphac {
namespace constructs {

class Coordinate2D {
 public:
  Coordinate2D(int x = 0, int y = 0);

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

  int get_x();
  int get_y();
  void set_x(int x);
  void set_y(int y);

 private:
  int x_;
  int y_;
};

}  // namespace constructs
}  // namespace morphac

#endif
