#ifndef SHAPES_H
#define SHAPES_H

#define _USE_MATH_DEFINES

#include <cmath>

#include "common/aliases/include/eigen_aliases.h"
#include "common/error_handling/include/error_macros.h"
#include "utils/include/numeric_utils.h"

namespace morphac {
namespace math {
namespace geometry {

struct ArcShape {
  const morphac::common::aliases::Point center;
  const double start_angle;
  const double end_angle;
  const double radius;

  ArcShape(const morphac::common::aliases::Point center,
           const double start_angle, const double end_angle,
           const double radius);
};

struct CircleShape {
  const morphac::common::aliases::Point center;
  const double radius;

  CircleShape(const morphac::common::aliases::Point center,
              const double radius);
};

struct RectangleShape {
  const morphac::common::aliases::Point center;
  const double size_x;
  const double size_y;
  const double angle;

  RectangleShape(const morphac::common::aliases::Point center,
                 const double size_x, const double size_y, const double angle);
};

struct RoundedRectangleShape {
  const morphac::common::aliases::Point center;
  const double size_x;
  const double size_y;
  const double angle;
  const double radius;

  RoundedRectangleShape(const morphac::common::aliases::Point center,
                        const double size_x, const double size_y,
                        const double angle, const double radius);
};

struct TriangleShape {
  const morphac::common::aliases::Point center;
  const double base;
  const double height;
  const double angle;

  TriangleShape(const morphac::common::aliases::Point center, const double base,
                const double height, const double angle);
};

}  // namespace geometry
}  // namespace math
}  // namespace morphac

#endif
