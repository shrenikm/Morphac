#include "utils/include/numeric_utils.h"

namespace morphac {
namespace utils {

using std::fabs;
using std::isinf;
using std::max;

// See: http://realtimecollisiondetection.net/blog/?p=89
bool IsEqual(const double value1, const double value2,
	     const double absolute_tolerance, const double relative_tolerance) {
  // Corner case when either of the values are infinity. In this case if we
  // execute the tolerance check, it will always return false.
  if (isinf(value1) || isinf(value2)) {
    return value1 == value2;
  }

  return fabs(value1 - value2) <=
	 max(absolute_tolerance,
	     relative_tolerance * max(fabs(value1), fabs(value2)));
}

}  // namespace utils
}  // namespace morphac
