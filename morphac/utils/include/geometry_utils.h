#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#define _USE_MATH_DEFINES

#include <math.h>

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"
#include "math/transforms/include/transforms.h"

namespace morphac {
namespace utils {

Eigen::MatrixXd TransformPolygon(const Eigen::MatrixXd& polygon,
                                 const double angle,
                                 const Eigen::Vector2d& translation);

Eigen::MatrixXd CreateRectangle(const double size_x, const double size_y,
                                const Eigen::Vector2d& center);

Eigen::MatrixXd CreateRoundedRectange(const double size_x, const double size_y,
                                      const double radius,
                                      const double angular_resolution,
                                      const Eigen::Vector2d& center);

Eigen::MatrixXd CreateArc(const double start_angle, const double end_angle,
                          const double radius, const double angular_resolution,
                          const Eigen::Vector2d& center);

Eigen::MatrixXd CreateCircle(const radius, const double angular_resolution,
                             const Eigen::Vector2d& center);

}  // namespace utils
}  // namespace morphac

#endif
