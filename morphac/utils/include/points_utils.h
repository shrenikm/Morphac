#ifndef POINTS_UTILS_H
#define POINTS_UTILS_H

#define _USE_MATH_DEFINES

#include <cmath>

#include "Eigen/Dense"

#include "common/aliases/include/eigen_aliases.h"
#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace utils {

morphac::common::aliases::HomogeneousPoints HomogenizePoints(
    const morphac::common::aliases::Points& points);

morphac::common::aliases::Points UnHomogenizePoints(
    const morphac::common::aliases::HomogeneousPoints& homogenous_points);

}  // namespace utils
}  // namespace morphac

#endif
