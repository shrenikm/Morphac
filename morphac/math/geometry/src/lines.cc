#include "math/geometry/include/lines.h"

namespace morphac {
namespace math {
namespace geometry {

using std::numeric_limits;

using Eigen::Vector2d;

using morphac::utils::IsEqual;

LineSpec ComputeLineSpec(const Vector2d& start_point,
                         const Vector2d& end_point) {
  double a = end_point(1) - start_point(1);
  double b = -(end_point(0) - start_point(0));
  double c = (end_point(0) - start_point(0)) * start_point(1) -
             (end_point(1) - start_point(1)) * start_point(0);
  double slope = numeric_limits<double>::infinity();

  // To avoid floating point issues, if the values are close enough to zero, we
  // set them to zero.
  if (IsEqual(a, 0.)) {
    a = 0.;
  }

  if (IsEqual(b, 0.)) {
    b = 0.;
  } else {
    // The slope is well defined in this case.
    // This is because the slope is (y2 - y1) / (x2 - x1) and if
    // b = -(x2 - x1) != 0, we can compute the division.
    slope = -a / b;
  }

  if (IsEqual(c, 0.)) {
    c = 0.;
  }

  return LineSpec{a, b, c, slope};
}

}  // namespace geometry
}  // namespace math
}  // namespace morphac
