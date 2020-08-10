#include "math/transforms/include/transforms.h"

namespace morphac {
namespace math {
namespace transforms {

using std::cos;
using std::sin;

using Eigen::MatrixXd;
using Eigen::Vector2d;

using morphac::constructs::Coordinate;

const MatrixXd RotationMatrix(const double angle) {
  MatrixXd rotation_matrix(2, 2);

  rotation_matrix << cos(angle), -sin(angle), sin(angle), cos(angle);

  return rotation_matrix;
}

const MatrixXd TransformationMatrix(const double angle,
                                    const Vector2d& translation) {
  MatrixXd transformation_matrix(3, 3);

  transformation_matrix << cos(angle), -sin(angle), translation(0), sin(angle),
      cos(angle), translation(1), 0, 0, 1;

  return transformation_matrix;
}

const MatrixXd TransformationMatrix(const double angle,
                                    const Coordinate& translation) {
  return TransformationMatrix(angle, translation.get_data());
}

}  // namespace transforms
}  // namespace math
}  // namespace morphac

