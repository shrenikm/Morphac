#include "math/transforms/include/transforms.h"

namespace morphac {
namespace math {
namespace transforms {

using std::cos;
using std::round;
using std::sin;
using std::vector;

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::VectorXi;

using morphac::common::aliases::HomogeneousPoints;
using morphac::common::aliases::Pixel;
using morphac::common::aliases::Pixels;
using morphac::common::aliases::Point;
using morphac::common::aliases::Points;
using morphac::utils::HomogenizePoints;
using morphac::utils::UnHomogenizePoints;

const MatrixXd RotationMatrix(const double angle) {
  MatrixXd rotation_matrix(2, 2);

  rotation_matrix << cos(angle), -sin(angle), sin(angle), cos(angle);

  return rotation_matrix;
}

const MatrixXd TransformationMatrix(const double angle,
                                    const Point& translation) {
  MatrixXd transformation_matrix(3, 3);

  transformation_matrix << cos(angle), -sin(angle), translation(0), sin(angle),
      cos(angle), translation(1), 0, 0, 1;

  return transformation_matrix;
}

Points TranslatePoints(const Points& points, const Point& translation) {
  return points.rowwise() + translation.transpose();
}

Points RotatePoints(const Points& points, const double angle,
                    const Point& center) {
  // First we translate such that the center is now the origin.
  Points rotated_points = TranslatePoints(points, -center);

  // Now we rotate.
  rotated_points =
      (RotationMatrix(angle) * rotated_points.transpose()).transpose();

  // Translating back.
  return TranslatePoints(rotated_points, center);
}

Points TransformPoints(const Points& points, const double angle,
                       const Point& translation) {
  return UnHomogenizePoints((TransformationMatrix(angle, translation) *
                             HomogenizePoints(points).transpose())
                                .transpose());
}

Point CanvasToWorld(const Pixel& canvas_coord, const double resolution,
                    const vector<int>& canvas_size) {
  MORPH_REQUIRE(resolution > 0, std::invalid_argument,
                "Resolution must be positive.");
  // The x and y coordinates need to be interchanged (Due to how matrices are
  // indexed).
  // The y coordinate needs to be inverted.
  Point world_coord = Point::Zero();
  world_coord(0) = canvas_coord(1);
  world_coord(1) = canvas_size.at(0) - canvas_coord(0);
  return resolution * world_coord;
}

Points CanvasToWorld(const Pixels& canvas_coords, const double resolution,
                     const vector<int>& canvas_size) {
  MORPH_REQUIRE(resolution > 0, std::invalid_argument,
                "Resolution must be positive.");
  const int num_points = canvas_coords.rows();
  Points world_coords = Points::Zero(num_points, 2);
  // The x and y coordinates need to be interchanged (Due to how matrices are
  // indexed).
  // The y coordinate needs to be inverted.

  world_coords.col(0) = canvas_coords.cast<double>().col(1);
  world_coords.col(1) = canvas_size.at(0) * VectorXd::Ones(num_points) -
                        canvas_coords.cast<double>().col(0);
  return resolution * world_coords;
}

double CanvasToWorld(const int scalar, const double resolution) {
  return scalar * resolution;
}

Pixel WorldToCanvas(const Point& world_coord, const double resolution,
                    const vector<int>& canvas_size) {
  MORPH_REQUIRE(resolution > 0, std::invalid_argument,
                "Resolution must be positive.");
  Pixel canvas_coord = Pixel::Zero();
  // Pixel canvas_coord =
  //    ((1 / resolution) * world_coord).array().round().matrix().cast<int>();

  // Interchange x and y and invert y.
  canvas_coord(0) =
      canvas_size.at(0) - round((1. / resolution) * world_coord(1));
  canvas_coord(1) = round((1. / resolution) * world_coord(0));

  return canvas_coord;

  // TODO: Determine if this out of bounds checking is required in the future.
  // if (canvas_size.size()) {
  //  MORPH_REQUIRE(canvas_size.size() == 2, std::invalid_argument,
  //                "Canvas size must be two dimensional.");
  //  // Check if the coordinate lies within the canvas.
  //  if ((canvas_coord(0) >= 0 && canvas_coord(0) < canvas_size[0]) &&
  //      (canvas_coord(1) >= 0 && canvas_coord(1) < canvas_size[1])) {
  //    return canvas_coord;
  //  } else {
  //    // Invalid coordinate.
  //    return -1 * Pixel::Ones(2);
  //  }
  //} else {
  //  // If not canvas size is provided, we don't care about the validity of
  //  // the point.
  //  return canvas_coord;
  //}
}

Pixels WorldToCanvas(const Points& world_coords, const double resolution,
                     const vector<int>& canvas_size) {
  MORPH_REQUIRE(resolution > 0, std::invalid_argument,
                "Resolution must be positive.");
  const int num_points = world_coords.rows();
  Pixels canvas_coords = Pixels::Zero(num_points, 2);
  // Pixels canvas_coords =
  //    ((1 / resolution) * world_coords).array().round().matrix().cast<int>();

  // Interchange x and y and invert y.
  canvas_coords.col(0) = canvas_size.at(0) * VectorXi::Ones(num_points) -
                         ((1 / resolution) * world_coords.col(1))
                             .array()
                             .round()
                             .matrix()
                             .cast<int>();
  canvas_coords.col(1) = ((1 / resolution) * world_coords.col(0))
                             .array()
                             .round()
                             .matrix()
                             .cast<int>();

  return canvas_coords;

  // TODO: Determine if this out of bounds checking is required in the future.
  // if (canvas_size.size()) {
  //  MORPH_REQUIRE(canvas_size.size() == 2, std::invalid_argument,
  //                "Canvas size must be two dimensional.");
  //  // Check if the coordinates lie within the canvas.
  //  for (int i = 0; i < canvas_coords.rows(); ++i) {
  //    if ((canvas_coords.row(i)(0) >= 0 &&
  //         canvas_coords.row(i)(0) < canvas_size[0]) &&
  //        (canvas_coords.row(i)(1) >= 0 &&
  //         canvas_coords.row(i)(1) < canvas_size[1])) {
  //    } else {
  //      // Invalid coordinate.
  //      canvas_coords.row(i) = -1 * Pixel::Ones();
  //    }
  //  }
  //}
  // return canvas_coords;
}

int WorldToCanvas(const double scalar, const double resolution) {
  return round(scalar / resolution);
}

}  // namespace transforms
}  // namespace math
}  // namespace morphac
