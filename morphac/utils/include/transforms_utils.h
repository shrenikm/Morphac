#ifndef TRANSFORMS_UTILS_H
#define TRANSFORMS_UTILS_H

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

Points TranslatePoints(const Points& points,
                       const Eigen::Vector2d& translation);

Points RotatePoints(const Points& points, const double angle,
                    const Eigen::Vector2d& center);

Points TransformPoints(const Points& points, const double angle,
                       const Eigen::Vector2d& translation);

}  // namespace utils
}  // namespace morphac

#endif
