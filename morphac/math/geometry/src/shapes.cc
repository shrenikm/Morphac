#include "math/geometry/include/shapes.h"

namespace morphac {
namespace math {
namespace geometry {

using morphac::common::aliases::Point;
using morphac::utils::IsEqual;

ArcShape::ArcShape(const double start_angle, const double end_angle,
                   const double radius, const Point& center)
    : start_angle(start_angle),
      end_angle(end_angle),
      radius(radius),
      center(center) {
  MORPH_REQUIRE(radius >= 0, std::invalid_argument, "Radius must be positive.");
  MORPH_REQUIRE(!IsEqual(start_angle, end_angle), std::invalid_argument,
                "The start and end angles must not be equal.");
}

CircleShape::CircleShape(const double radius, const Point& center)
    : radius(radius), center(center) {
  MORPH_REQUIRE(radius >= 0, std::invalid_argument, "Radius must be positive.");
}

RectangleShape::RectangleShape(const double size_x, const double size_y,
                               const double angle, const Point& center)
    : size_x(size_x), size_y(size_y), angle(angle), center(center) {
  // The reason the conditions are >= 0 and not > 0 is because sometimes
  // rounded rectangle polygon creation may call this function with a zero size.
  MORPH_REQUIRE(size_x >= 0, std::invalid_argument,
                "Size along the x axis must be positive");
  MORPH_REQUIRE(size_y >= 0, std::invalid_argument,
                "Size along the y axis must be positive");
}

RoundedRectangleShape::RoundedRectangleShape(const double size_x,
                                             const double size_y,
                                             const double angle,
                                             const double radius,
                                             const Point& center)
    : size_x(size_x),
      size_y(size_y),
      angle(angle),
      radius(radius),
      center(center) {
  // The reason the conditions are >= 0 and not > 0 is because sometimes
  // rounded rectangle polygon creation may call this function with a zero size.
  MORPH_REQUIRE(size_x >= 0, std::invalid_argument,
                "Size along the x axis must be positive");
  MORPH_REQUIRE(size_y >= 0, std::invalid_argument,
                "Size along the y axis must be positive");
  MORPH_REQUIRE(radius >= 0, std::invalid_argument, "Radius must be positive.");
  // Test for the radius validity.
  MORPH_REQUIRE(radius <= (size_x / 2) && radius <= (size_y / 2),
                std::invalid_argument,
                "The radius is too large compared to the rectangle sizes.");
}

TriangleShape::TriangleShape(const double base, const double height,
                             const double angle, const Point& center)
    : base(base), height(height), angle(angle), center(center) {
  MORPH_REQUIRE(base >= 0, std::invalid_argument, "Base must be positive");
  MORPH_REQUIRE(height >= 0, std::invalid_argument, "Height must be positive");
}

}  // namespace geometry
}  // namespace math
}  // namespace morphac
