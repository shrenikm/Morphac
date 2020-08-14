#include "utils/include/geometry_utils.h"

namespace morphac {
namespace utils {

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::VectorXd;

using morphac::math::transforms::TransformationMatrix;

MatrixXd TransformPolygon(const MatrixXd& polygon, const double angle,
                          const Vector2d& translation) {
  MORPH_REQUIRE(polygon.rows() > 0 && polygon.cols() == 2,
                std::invalid_argument, "The polygon must be of size n x 2.");
  return (TransformationMatrix(angle, translation) * polygon.transpose())
      .transpose();
}

// MatrixXd CreateRectangle(const double size_x, const double size_y,
//                         const Vector2d& center) {
//  MatrixXd rectangle(4, 2);
//  rectangle << -size_x / 2, size_y / 2, size_x / 2, size_y / 2, size_x / 2,
//      -size_y / 2, -size_x / 2, -size_y / 2;
//
//  return rectangle;
//}

}  // namespace utils
}  // namespace morphac
