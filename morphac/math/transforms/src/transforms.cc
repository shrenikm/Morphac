#include "math/transforms/include/transforms.h"

namespace morphac {
namespace math {
namespace transforms {

using std::cos;
using std::sin;
using std::vector;

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::Vector2i;

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

Vector2d CanvasToWorld(const Vector2i& canvas_coord, const double resolution) {
  MORPH_REQUIRE(resolution > 0, std::invalid_argument,
                "Resolution must be positive.");
  return resolution * canvas_coord.cast<double>();
}

Vector2i WorldToCanvas(const Vector2d& world_coord, const double resolution,
                       const vector<int>& canvas_size) {
  MORPH_REQUIRE(resolution > 0, std::invalid_argument,
                "Resolution must be positive.");
  Vector2i canvas_coord =
      ((1 / resolution) * world_coord).array().round().matrix().cast<int>();

  if (canvas_size.size()) {
    MORPH_REQUIRE(
        canvas_size.size() == 2, std::invalid_argument,
        "If the canvas size is provided, it must be two dimensional.");
    // Check if the coordinate lies within the canvas.
    if ((canvas_coord(0) >= 0 && canvas_coord[0] < canvas_size[0]) &&
        (canvas_coord(1) >= 0 && canvas_coord[1] < canvas_size[1])) {
      return canvas_coord;
    } else {
      // Invalid coordinate.
      return -1 * Vector2i::Ones(2);
    }
  } else {
    // If not canvas size is provided, we don't care about the validity of
    // the point.
    return canvas_coord;
  }
}

}  // namespace transforms
}  // namespace math
}  // namespace morphac

