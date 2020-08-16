#include "utils/include/transforms_utils.h"

namespace morphac {
namespace utils {

using Eigen::Vector2d;
using Eigen::VectorXd;

using morphac::math::transforms::RotationMatrix;
using morphac::math::transforms::TransformationMatrix;

HomogeneousPoints HomogenizePoints(const Points& points) {
  HomogeneousPoints homogeneous_points(points.rows(), 3);
  homogeneous_points << points, VectorXd::Ones(points.rows());
  return homogeneous_points;
}

Points UnHomogenizePoints(const HomogeneousPoints& homogeneous_points) {
  return homogeneous_points.block(0, 0, homogeneous_points.rows(), 2);
}

Points TransformPoints(const Points& points, const double angle,
                       const Vector2d& translation) {
  return UnHomogenizePoints((TransformationMatrix(angle, translation) *
                             HomogenizePoints(points).transpose())
                                .transpose());
}

}  // namespace utils
}  // namespace morphac
