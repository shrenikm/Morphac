#ifndef NUMERIC_UTILS_H
#define NUMERIC_UTILS_H

#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>
#include <limits>

#include "common/aliases/include/numeric_aliases.h"

namespace morphac {
namespace utils {

// Functions to check the equality between values. Overload this for different
// argument types.
// For mobile robots, while we deal with measurements in meters, a tolerance of
// 1e-6 (Using 1e-7) is sufficient for an equality check.
bool IsEqual(const double value1, const double value2,
             // We could also use Epsilon<double> here for more accurate checks
             // if needed.
             const double absolute_tolerance = 1e-7,
             const double relative_tolerance = 1e-7);

}  // namespace utils
}  // namespace morphac

#endif
