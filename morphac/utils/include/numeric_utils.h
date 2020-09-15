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
bool IsEqual(
    const double value1, const double value2,
    const double absolute_tolerance = morphac::common::aliases::Epsilon<double>,
    const double relative_tolerance = 1e-9);

}  // namespace utils
}  // namespace morphac

#endif
