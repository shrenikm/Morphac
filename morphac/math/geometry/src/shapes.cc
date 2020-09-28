#include "math/geometry/include/shapes.h"

namespace morphac {
namespace math {
namespace geometry {

using morphac::common::aliases::Point;

ArcShape::ArcShape(const Point center, const double start_angle,
                   const double end_angle, const double radius)
    : center(center),
      start_angle(start_angle),
      end_angle(end_angle),
      radius(radius) {}

CircleShape::CircleShape(const Point center, const double radius)
    : center(center), radius(radius) {}

RectangleShape::RectangleShape(const Point center, const double size_x,
                               const double size_y, const double angle)
    : center(center), size_x(size_x), size_y(size_y), angle(angle) {}

RoundedRectangleShape::RoundedRectangleShape(const Point center,
                                             const double size_x,
                                             const double size_y,
                                             const double angle,
                                             const double radius)
    : center(center),
      size_x(size_x),
      size_y(size_y),
      angle(angle),
      radius(radius) {}

TriangleShape::TriangleShape(const Point center, const double base,
                             const double height, const double angle)
    : center(center), base(base), height(height), angle(angle) {}

}  // namespace geometry
}  // namespace math
}  // namespace morphac
