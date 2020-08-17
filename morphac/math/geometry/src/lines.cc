#include "math/geometry/include/lines.h"

namespace morphac {
namespace math {
namespace geometry {

using Eigen::Vector2d;

LineSpec ComputeLineSpec(const Vector2d& start_point,
                         const Vector2d& end_point) {
  double a = 0;
  double b = 0;
  double c = 0;
  double slope =
      (end_point(1) - start_point(1)) / (end_point(0) - start_point(0));
  return LineSpec{a, b, c, slope};
}

}  // namespace geometry
}  // namespace math
}  // namespace morphac
