#ifndef POLYGONS_H
#define POLYGONS_H

#define _USE_MATH_DEFINES

#include <cmath>

#include "Eigen/Dense"
#include "common/aliases/include/eigen_aliases.h"
#include "common/error_handling/include/error_macros.h"
#include "math/transforms/include/transforms.h"
#include "utils/include/points_utils.h"

namespace morphac {
namespace math {
namespace geometry {

morphac::common::aliases::Points CreateArc(
    const double start_angle, const double end_angle, const double radius,
    const double angular_resolution,
    const Eigen::Vector2d& center = Eigen::Vector2d::Zero());

morphac::common::aliases::Points CreateCircularPolygon(
    const double radius, const double angular_resolution,
    const Eigen::Vector2d& center = Eigen::Vector2d::Zero());

morphac::common::aliases::Points CreateRectangularPolygon(
    const double size_x, const double size_y, const double angle,
    const Eigen::Vector2d& center = Eigen::Vector2d::Zero());

morphac::common::aliases::Points CreateRoundedRectangularPolygon(
    const double size_x, const double size_y, const double angle,
    const double radius, const double angular_resolution,
    const Eigen::Vector2d& center = Eigen::Vector2d::Zero());

morphac::common::aliases::Points CreateTriangularPolygon(
    const double base, const double height, const double angle,
    const Eigen::Vector2d& center = Eigen::Vector2d::Zero());

}  // namespace geometry
}  // namespace math
}  // namespace morphac

#endif
