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
  const double start_angle;
  const double end_angle;
  const double radius;
  const morphac::common::aliases::Point center;

  ArcShape(const double start_angle, const double end_angle,
           const double radius,
           const morphac::common::aliases::Point center =
               morphac::common::aliases::Point::Zero());
};

struct CircleShape {
  const double radius;
  const morphac::common::aliases::Point center;

  CircleShape(const double radius,
              const morphac::common::aliases::Point center =
                  morphac::common::aliases::Point::Zero());
};

struct RectangleShape {
  const double size_x;
  const double size_y;
  const double angle;
  const morphac::common::aliases::Point center;

  RectangleShape(const double size_x, const double size_y, const double angle,
                 const morphac::common::aliases::Point center =
                     morphac::common::aliases::Point::Zero());
};

struct RoundedRectangleShape {
  const double size_x;
  const double size_y;
  const double angle;
  const double radius;
  const morphac::common::aliases::Point center;

  RoundedRectangleShape(const double size_x, const double size_y,
                        const double angle, const double radius,
                        const morphac::common::aliases::Point center =
                            morphac::common::aliases::Point::Zero());
};

struct TriangleShape {
  const double base;
  const double height;
  const double angle;
  const morphac::common::aliases::Point center;

  TriangleShape(const double base, const double height, const double angle,
                const morphac::common::aliases::Point center =
                    morphac::common::aliases::Point::Zero());
};

}  // namespace geometry
}  // namespace math
}  // namespace morphac

#endif
