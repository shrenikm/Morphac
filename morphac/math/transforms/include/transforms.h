#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "Eigen/Dense"

#include "constructs/include/coordinate.h"

namespace morphac {
namespace math {
namespace transforms {

const Eigen::MatrixXd RotationMatrix(const double angle);

const Eigen::MatrixXd TransformationMatrix(const double angle,
                                           const Eigen::Vector2d& translation);

const Eigen::MatrixXd TransformationMatrix(
    const double angle, const morphac::constructs::Coordinate& translation);

}  // namespace transforms
}  // namespace math
}  // namespace morphac

#endif
