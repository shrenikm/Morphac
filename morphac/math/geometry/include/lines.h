#ifndef LINES_H
#define LINES_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <sstream>

#include "Eigen/Dense"
#include "common/aliases/include/eigen_aliases.h"
#include "common/aliases/include/numeric_aliases.h"
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
  const double slope;
  const double x_intercept;
  const double y_intercept;

  LineSpec(const double slope, const double x_intercept,
           const double y_intercept);

  // Comparison operators for LineSpec. We define these ourselves so that we can
  // use our float comparison functions to ensure robust checking.
  // We could also make these non friend, but we make the decision to packaging
  // it all up inside the class.
  friend bool operator==(const LineSpec& line_spec1,
                         const LineSpec& line_spec2);
  friend bool operator!=(const LineSpec& line_spec1,
                         const LineSpec& line_spec2);

  friend std::ostream& operator<<(std::ostream& os, const LineSpec& line_spec);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;
};

struct PointProjection {
  const double distance;
  const double alpha;
  const morphac::common::aliases::Point projection;

  PointProjection(const double distance, const double alpha,
                  const morphac::common::aliases::Point& point);
};

LineSpec ComputeLineSpec(const morphac::common::aliases::Point& start_point,
                         const morphac::common::aliases::Point& end_point);

bool AreLinesParallel(const LineSpec& line_spec1, const LineSpec& line_spec2);

bool AreLinesParallel(const morphac::common::aliases::Point& start_point1,
                      const morphac::common::aliases::Point& end_point1,
                      const morphac::common::aliases::Point& start_point2,
                      const morphac::common::aliases::Point& end_point2);

bool AreLinesPerpendicular(const LineSpec& line_spec1,
                           const LineSpec& line_spec2);

bool AreLinesPerpendicular(const morphac::common::aliases::Point& start_point1,
                           const morphac::common::aliases::Point& end_point1,
                           const morphac::common::aliases::Point& start_point2,
                           const morphac::common::aliases::Point& end_point2);

PointProjection ComputePointProjection(
    const morphac::common::aliases::Point& point,
    const morphac::common::aliases::Point& start_point,
    const morphac::common::aliases::Point& end_point);

PointProjection ComputePointProjection(
    const morphac::common::aliases::Point& point, const LineSpec& line_spec);

}  // namespace geometry
}  // namespace math
}  // namespace morphac

#endif
