#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#define _USE_MATH_DEFINES

#include <math.h>

#include "Eigen/Dense"

#include "utils/include/numeric_utils.h"

namespace morphac {
namespace math {
namespace geometry {

struct LineSpec {
  // These are const as there is not reason (for now) to modify these values
  // once created. Modification is required when the actual line changes, in
  // which case it is better to recreate such an object.
  // This also means that we don't have copy/assignment constructors, which
  // isn't that big of an issue.
  const double a;
  const double b;
  const double c;
  const double slope;
};

LineSpec ComputeLineSpec(const Eigen::Vector2d& start_point,
                         const Eigen::Vector2d& end_point);

bool AreLinesParallel(const LineSpec& line_spec1, const LineSpec& line_spec2);

bool AreLinesParallel(const Eigen::Vector2d& start_point1,
                      const Eigen::Vector2d& end_point1,
                      const Eigen::Vector2d& start_point2,
                      const Eigen::Vector2d& end_point2);

bool AreLinesPerpendicular(const LineSpec& line_spec1,
                           const LineSpec& line_spec2);

bool AreLinesPerpendicular(const Eigen::Vector2d& start_point1,
                           const Eigen::Vector2d& end_point1,
                           const Eigen::Vector2d& start_point2,
                           const Eigen::Vector2d& end_point2);

}  // namespace geometry
}  // namespace math
}  // namespace morphac

#endif
