#ifndef ANGLE_UTILS_H
#define ANGLE_UTILS_H

#define _USE_MATH_DEFINES

#include <cmath>

namespace morphac {
namespace utils {

double ToDegrees(const double angle_in_radians);
double ToRadians(const double angle_in_degrees);

double NormalizeAngle(const double angle_in_radians);

}  // namespace utils
}  // namespace morphac

#endif
