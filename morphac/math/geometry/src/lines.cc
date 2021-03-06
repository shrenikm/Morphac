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

using morphac::common::aliases::Epsilon;
using morphac::common::aliases::Infinity;
using morphac::common::aliases::Point;
using morphac::utils::IsEqual;

LineSpec::LineSpec(const double slope, const double x_intercept,
                   const double y_intercept)
    : slope(slope), x_intercept(x_intercept), y_intercept(y_intercept) {}

bool operator==(const LineSpec& line_spec1, const LineSpec& line_spec2) {
  return IsEqual(line_spec1.slope, line_spec2.slope) &&
         IsEqual(line_spec1.x_intercept, line_spec2.x_intercept) &&
         IsEqual(line_spec1.y_intercept, line_spec2.y_intercept);
}

bool operator!=(const LineSpec& line_spec1, const LineSpec& line_spec2) {
  return !(line_spec1 == line_spec2);
}

ostream& operator<<(ostream& os, const LineSpec& line_spec) {
  os << "LineSpec[" << line_spec.slope << " " << line_spec.x_intercept << " "
     << line_spec.y_intercept << "]";
  return os;
}

string LineSpec::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

LineSpec ComputeLineSpec(const Point& start_point, const Point& end_point) {
  double slope = Infinity<double>;
  double x_intercept = Infinity<double>;
  double y_intercept = Infinity<double>;

  if (!IsEqual(start_point(0), end_point(0))) {
    // The slope is well defined.
    slope = (end_point(1) - start_point(1)) / (end_point(0) - start_point(0));
  }

  // The y intercept is infinity if the slope is infinity.
  if (!isinf(slope)) {
    y_intercept = start_point(1) - slope * start_point(0);
  } else {
    // Special case when the slope is inf and the line passes through the
    // origin. In this case, the intercept is not infinity, but zero.
    if (IsEqual(start_point(0), 0.)) {
      y_intercept = 0.;
    }
  }

  // The x intercept is infinity if the slope is zero.
  if (!IsEqual(slope, 0.)) {
    // If the y intercept is also infinity, the x intercept is just the x
    // coordinate.
    if (isinf(y_intercept)) {
      x_intercept = start_point(0);
    } else {
      x_intercept = -y_intercept / slope;
    }
  } else {
    // Special case then the slope is zero and the line passes through the
    // origin. In this case, the intercept is not infinity, but zero.
    if (IsEqual(start_point(1), 0.)) {
      x_intercept = 0.;
    }
  }

  return LineSpec{slope, x_intercept, y_intercept};
}

bool AreLinesParallel(const LineSpec& line_spec1, const LineSpec& line_spec2) {
  return IsEqual(line_spec1.slope, line_spec2.slope);
}

bool AreLinesParallel(const Point& start_point1, const Point& end_point1,
                      const Point& start_point2, const Point& end_point2) {
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

bool AreLinesPerpendicular(const Point& start_point1, const Point& end_point1,
                           const Point& start_point2, const Point& end_point2) {
  return AreLinesPerpendicular(ComputeLineSpec(start_point1, end_point1),
                               ComputeLineSpec(start_point2, end_point2));
}

}  // namespace geometry
}  // namespace math
}  // namespace morphac
