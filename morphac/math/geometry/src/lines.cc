#include "math/geometry/include/lines.h"

namespace morphac {
namespace math {
namespace geometry {

using std::endl;
using std::isinf;
using std::numeric_limits;
using std::ostream;
using std::ostringstream;
using std::pow;
using std::sqrt;
using std::string;

using morphac::common::aliases::Epsilon;
using morphac::common::aliases::Infinity;
using morphac::common::aliases::Point;
using morphac::utils::IsEqual;

LineSpec::LineSpec(const double slope, const double x_intercept,
                   const double y_intercept)
    : slope(slope),
      x_intercept(x_intercept),
      y_intercept(y_intercept) {  // Both intercepts cannot be infinity.
  MORPH_REQUIRE(!isinf(x_intercept) || !isinf(y_intercept),
                std::invalid_argument,
                "Both the intercepts cannot be infinity.");
  // If the slope is 0., we require the x intercept to be inf or both the x and
  // y intercepts to be 0.
  if (IsEqual(slope, 0.)) {
    MORPH_REQUIRE(isinf(x_intercept) ||
                      (IsEqual(x_intercept, 0.) && IsEqual(y_intercept, 0.)),
                  std::invalid_argument,
                  "Slope and intercepts are incompatible.");
  }
  // If the slope is inf, we require the y intercept to be inf or both the x
  // and y intercepts to be 0.
  else if (isinf(slope)) {
    MORPH_REQUIRE(isinf(y_intercept) ||
                      (IsEqual(x_intercept, 0.) && IsEqual(y_intercept, 0.)),
                  std::invalid_argument,
                  "Slope and intercepts are incompatible.");
  }
  // If the slope is not 0 or inf, we conduct a regular slope test.
  else {
    // We only test if both the intercepts are not zero. This is because if
    // they are both zero, the slope can take any value.
    if (!IsEqual(x_intercept, 0.) || !IsEqual(y_intercept, 0.)) {
      MORPH_REQUIRE(
          IsEqual(-y_intercept / x_intercept, slope), std::invalid_argument,
          "Slope and intercept values are not compatible. They do not "
          "correspond to a line.");
    }
  }
}

PointProjection::PointProjection(const double distance, const double alpha,
                                 const Point& projection)
    : distance(distance), alpha(alpha), projection(projection) {
  // Distance must be non-negative.
  MORPH_REQUIRE(distance >= 0, std::invalid_argument,
                "Distance cannot be negative.");
}

PointProjection::PointProjection(const double distance, const Point& projection)
    : distance(distance), alpha(Infinity<double>), projection(projection) {
  // Distance must be non-negative.
  MORPH_REQUIRE(distance >= 0, std::invalid_argument,
                "Distance cannot be negative.");
}

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

PointProjection ComputePointProjection(const Point& point,
                                       const Point& start_point,
                                       const Point& end_point) {
  // Note that this function is slightly more efficient that the one that
  // takes in LineSpec as the other overload calls this function at the end.
  Point line_segment = end_point - start_point;
  double alpha =
      line_segment.dot(point - start_point) / line_segment.squaredNorm();
  Point projection = start_point + alpha * (end_point - start_point);
  double distance = (point - projection).norm();

  return PointProjection{distance, alpha, projection};
}

PointProjection ComputePointProjection(const Point& point,
                                       const LineSpec& line_spec) {
  // We extract a segment from this line and call the overload with the end
  // points. As the alpha parameter does not make sense for projecting on an
  // infinite line, we set it to infinity. The distance and projection values
  // will hold regardless.
  Point start_point;
  Point end_point;

  // We find a single point on the line as the start point. As one of the
  // intercepts need to be non inf, we use this intercept and set the other
  // coordinate to zero to find this point.
  if (!isinf(line_spec.x_intercept)) {
    start_point = Point(line_spec.x_intercept, 0.);
  } else {
    start_point = Point(0., line_spec.y_intercept);
  }

  // Once we have the start point, we construct a unit vector in the direction
  // of the slope. To do this we compute the cos and sin of the line's angle
  // wrt to the x axis.
  // We use 1 + (tan)^2 = sec^2 to find cos.

  double cos_theta = sqrt(1 / (1 + pow(line_spec.slope, 2)));
  double sin_theta = sqrt(1 - pow(cos_theta, 2));
  Point unit_vector(cos_theta, sin_theta);

  // We get the second end point by adding the unit vector to the start point.
  // This gives us two points on the line after which we can find the
  // projection by calling the overloaded function.
  end_point = start_point + unit_vector;

  PointProjection point_projection{
      ComputePointProjection(point, start_point, end_point)};
  return PointProjection{point_projection.distance,
                         point_projection.projection};
}

bool IsPointOnLine(const Point& point, const Point& start_point,
                   const Point& end_point) {
  // Computing the projection. If the distance is zero and alpha is between 0
  // and 1, the point lies on the line and is within the segment.
  auto point_projection = ComputePointProjection(point, start_point, end_point);

  if (IsEqual(point_projection.distance, 0.) &&
      (point_projection.alpha >= 0 && point_projection.alpha <= 1)) {
    return true;
  } else {
    return false;
  }
}

bool IsPointOnLine(const Point& point, const LineSpec& line_spec) {
  // Computing the projection. If the distance is zero, it means the point
  // lies on the line. Here we don't use the alpha values as it is not a line
  // segment.
  auto point_projection = ComputePointProjection(point, line_spec);

  if (IsEqual(point_projection.distance, 0.)) {
    return true;
  } else {
    return false;
  }
}

}  // namespace geometry
}  // namespace math
}  // namespace morphac
