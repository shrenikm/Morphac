#include "math/geometry/include/shapes.h"

namespace morphac {
namespace math {
namespace geometry {

using morphac::common::aliases::Point;
using morphac::utils::IsEqual;

ArcShape::ArcShape(const Point center, const double start_angle,
                   const double end_angle, const double radius)
    : center(center),
      start_angle(start_angle),
      end_angle(end_angle),
      radius(radius) {
  MORPH_REQUIRE(radius > 0, std::invalid_argument, "Radius must be positive.");
  MORPH_REQUIRE(!IsEqual(start_angle, end_angle), std::invalid_argument,
                "The start and end angles must not be equal.");
}

CircleShape::CircleShape(const Point center, const double radius)
    : center(center), radius(radius) {
  MORPH_REQUIRE(radius > 0, std::invalid_argument, "Radius must be positive.");
}

RectangleShape::RectangleShape(const Point center, const double size_x,
                               const double size_y, const double angle)
    : center(center), size_x(size_x), size_y(size_y), angle(angle) {
  MORPH_REQUIRE(size_x > 0, std::invalid_argument,
                "Size along the x axis must be positive");
  MORPH_REQUIRE(size_y > 0, std::invalid_argument,
                "Size along the y axis must be positive");
}

RoundedRectangleShape::RoundedRectangleShape(const Point center,
                                             const double size_x,
                                             const double size_y,
                                             const double angle,
                                             const double radius)
    : center(center),
      size_x(size_x),
      size_y(size_y),
      angle(angle),
      radius(radius) {
  MORPH_REQUIRE(size_x > 0, std::invalid_argument,
                "Size along the x axis must be positive");
  MORPH_REQUIRE(radius > 0, std::invalid_argument,
                "Size along the y axis must be positive");
  MORPH_REQUIRE(radius > 0, std::invalid_argument, "Radius must be positive.");
  // Test for the radius validity.
  MORPH_REQUIRE(radius <= (size_x / 2) && radius <= (size_y / 2),
                std::invalid_argument,
                "The radius is too large compared to the rectangle sizes.");
}

TriangleShape::TriangleShape(const Point center, const double base,
                             const double height, const double angle)
    : center(center), base(base), height(height), angle(angle) {
  MORPH_REQUIRE(base > 0, std::invalid_argument, "Base must be positive");
  MORPH_REQUIRE(height > 0, std::invalid_argument, "Height must be positive");
}

}  // namespace geometry
}  // namespace math
}  // namespace morphac
