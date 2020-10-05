#include "utils/include/points_utils.h"

namespace morphac {
namespace utils {

using Eigen::VectorXd;

using morphac::common::aliases::HomogeneousPoints;
using morphac::common::aliases::Points;

HomogeneousPoints HomogenizePoints(const Points& points) {
  HomogeneousPoints homogeneous_points(points.rows(), 3);
  homogeneous_points << points, VectorXd::Ones(points.rows());
  return homogeneous_points;
}

Points UnHomogenizePoints(const HomogeneousPoints& homogeneous_points) {
  return homogeneous_points.block(0, 0, homogeneous_points.rows(), 2);
}

}  // namespace utils
}  // namespace morphac
