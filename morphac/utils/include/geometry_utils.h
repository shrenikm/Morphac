#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#define _USE_MATH_DEFINES

#include <cmath>

#include "Eigen/Dense"

#include "common/aliases/include/eigen_aliases.h"
#include "common/error_handling/include/error_macros.h"
#include "math/transforms/include/transforms.h"
#include "utils/include/transforms_utils.h"

namespace morphac {
namespace utils {

morphac::common::aliases::Points CreateRectangularPolygon(
    const double size_x, const double size_y, const double angle,
    const Eigen::Vector2d& center);

morphac::common::aliases::Points CreateArc(const double start_angle,
                                           const double end_angle,
                                           const double radius,
                                           const double angular_resolution,
                                           const Eigen::Vector2d& center);

morphac::common::aliases::Points CreateCircularPolygon(
    const double radius, const double angular_resolution,
    const Eigen::Vector2d& center);

morphac::common::aliases::Points CreateRoundedRectangularPolygon(
    const double size_x, const double size_y, const double angle,
    const double radius, const double angular_resolution,
    const Eigen::Vector2d& center);

}  // namespace utils
}  // namespace morphac

#endif
