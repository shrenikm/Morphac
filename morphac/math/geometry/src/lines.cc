#include "math/geometry/include/lines.h"

namespace morphac {
namespace math {
namespace geometry {

using std::endl;
using std::isinf;
using std::numeric_limits;
using std::ostream;
using std::ostringstream;
using std::string;

using Eigen::Vector2d;

using morphac::utils::IsEqual;

bool operator==(const LineSpec& line_spec1, const LineSpec& line_spec2) {
  return IsEqual(line_spec1.a, line_spec2.a) &&
         IsEqual(line_spec1.b, line_spec2.b) &&
         IsEqual(line_spec1.c, line_spec2.c) &&
         IsEqual(line_spec1.slope, line_spec2.slope);
}

bool operator!=(const LineSpec& line_spec1, const LineSpec& line_spec2) {
  return !(line_spec1 == line_spec2);
}

ostream& operator<<(ostream& os, const LineSpec& line_spec) {
  os << "LineSpec[" << line_spec.a << " " << line_spec.b << " " << line_spec.c
     << " " << line_spec.slope << "]";
  return os;
}

string LineSpec::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

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

bool AreLinesParallel(const LineSpec& line_spec1, const LineSpec& line_spec2) {
  return IsEqual(line_spec1.slope, line_spec2.slope);
}

bool AreLinesParallel(const Vector2d& start_point1, const Vector2d& end_point1,
                      const Vector2d& start_point2,
                      const Vector2d& end_point2) {
  return AreLinesParallel(ComputeLineSpec(start_point1, end_point1),
                          ComputeLineSpec(start_point2, end_point2));
}

bool AreLinesPerpendicular(const LineSpec& line_spec1,
                           const LineSpec& line_spec2) {
  // The only special condition is when one of the slopes is infinity and the
  // other is zero. In this case, they are perpendicular.
  if ((isinf(line_spec1.slope) && IsEqual(line_spec2.slope, 0.)) ||
      ((IsEqual(line_spec1.slope, 0.) && isinf(line_spec2.slope)))) {
    return true;
  }

  if (IsEqual(line_spec1.slope * line_spec2.slope, -1)) {
    return true;
  } else {
    return false;
  }
}

bool AreLinesPerpendicular(const Vector2d& start_point1,
                           const Vector2d& end_point1,
                           const Vector2d& start_point2,
                           const Vector2d& end_point2) {
  return AreLinesPerpendicular(ComputeLineSpec(start_point1, end_point1),
                               ComputeLineSpec(start_point2, end_point2));
}

}  // namespace geometry
}  // namespace math
}  // namespace morphac
