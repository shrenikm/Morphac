#include "utils/include/angle_utils.h"

namespace morphac {
namespace math {
namespace utils {

double ToDegrees(const double angle_in_radians) {
  // From radians to degrees.
  return 180. * angle_in_radians / M_PI;
}

double ToRadians(const double angle_in_degrees) {
  // From degrees to radians.
  return M_PI * angle_in_degrees / 180.;
}

double NormalizeAngle(const double angle_in_radians) {
  // Getting the angle within 2 * pi.
  double normalized_angle = fmod(angle_in_radians, (2 * M_PI));

  // Making sure that abs(angle) <= pi.
  if (normalized_angle > M_PI) {
    // Needs to be negative.
    return -(2 * M_PI - normalized_angle);
  }

  if (normalized_angle <= -M_PI) {
    // Needs to be positive.
    return 2 * M_PI + normalized_angle;
  }

  return normalized_angle;
}

}  // namespace utils
}  // namespace math
}  // namespace morphac
