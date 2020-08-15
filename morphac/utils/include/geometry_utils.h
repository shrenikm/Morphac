#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#define _USE_MATH_DEFINES

#include <math.h>

#include "Eigen/Dense"

#include "common/aliases/include/eigen_aliases.h"
#include "common/error_handling/include/error_macros.h"
#include "math/transforms/include/transforms.h"

namespace morphac {
namespace utils {

HomogeneousPoints HomogenizePoints(const Points& points);

Points UnHomogenizePoints(const HomogeneousPoints& homogenous_points);

Points TransformPoints(const Points& points, const double angle,
                       const Eigen::Vector2d& translation);

Points CreateRectangularPolygon(const double size_x, const double size_y,
                                const double angle,
                                const Eigen::Vector2d& center);

Points CreateArc(const double start_angle, const double end_angle,
                 const double radius, const double angular_resolution,
                 const Eigen::Vector2d& center);

Points CreateCircularPolygon(const double radius,
                             const double angular_resolution,
                             const Eigen::Vector2d& center);

Points CreateRoundedRectangularPolygon(const double size_x, const double size_y,
                                       const double radius,
                                       const double angular_resolution,
                                       const double angle,
                                       const Eigen::Vector2d& center);

}  // namespace utils
}  // namespace morphac

#endif
