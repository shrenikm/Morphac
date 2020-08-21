#ifndef TRANSFORMS_UTILS_H
#define TRANSFORMS_UTILS_H

#define _USE_MATH_DEFINES

#include <cmath>

#include "Eigen/Dense"

#include "common/aliases/include/eigen_aliases.h"
#include "common/error_handling/include/error_macros.h"
#include "math/transforms/include/transforms.h"

namespace morphac {
namespace utils {

morphac::common::aliases::HomogeneousPoints HomogenizePoints(
    const morphac::common::aliases::Points& points);

morphac::common::aliases::Points UnHomogenizePoints(
    const morphac::common::aliases::HomogeneousPoints& homogenous_points);

morphac::common::aliases::Points TranslatePoints(
    const morphac::common::aliases::Points& points,
    const Eigen::Vector2d& translation);

morphac::common::aliases::Points RotatePoints(
    const morphac::common::aliases::Points& points, const double angle,
    const Eigen::Vector2d& center = Eigen::Vector2d::Zero());

morphac::common::aliases::Points TransformPoints(
    const morphac::common::aliases::Points& points, const double angle,
    const Eigen::Vector2d& translation);

}  // namespace utils
}  // namespace morphac

#endif
