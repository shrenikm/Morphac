#ifndef NUMERIC_UTILS_H
#define NUMERIC_UTILS_H

#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>
#include <limits>

namespace morphac {
namespace utils {

// Functions to check the equality between values. Overload this for different
// argument types.
bool IsEqual(
    const double value1, const double value2,
    const double absolute_tolerance = std::numeric_limits<double>::epsilon(),
    const double relative_tolerance = 1e-9);

}  // namespace utils
}  // namespace morphac

#endif
