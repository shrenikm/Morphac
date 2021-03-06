#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include <vector>

#include "Eigen/Dense"
#include "common/aliases/include/eigen_aliases.h"
#include "common/error_handling/include/error_macros.h"
#include "utils/include/points_utils.h"

namespace morphac {
namespace math {
namespace transforms {

// These functions need to be fast, so we don't use the Coordinate construct and
// represent all coordinates as a Point/Pixel (Eigen aliases). If Coordinates
// are required, it should be easy enough to convert them to vectors in the
// argument and wrap them as Coordinates while returning.

const Eigen::MatrixXd RotationMatrix(const double angle);

const Eigen::MatrixXd TransformationMatrix(
    const double angle, const morphac::common::aliases::Point& translation);

morphac::common::aliases::Points TranslatePoints(
    const morphac::common::aliases::Points& points,
    const morphac::common::aliases::Point& translation);

morphac::common::aliases::Points RotatePoints(
    const morphac::common::aliases::Points& points, const double angle,
    const morphac::common::aliases::Point& center =
        morphac::common::aliases::Point::Zero());

morphac::common::aliases::Points TransformPoints(
    const morphac::common::aliases::Points& points, const double angle,
    const morphac::common::aliases::Point& translation);

morphac::common::aliases::Point CanvasToWorld(
    const morphac::common::aliases::Pixel& canvas_coord,
    const double resolution, const std::vector<int>& canvas_size);

morphac::common::aliases::Points CanvasToWorld(
    const morphac::common::aliases::Pixels& canvas_coords,
    const double resolution, const std::vector<int>& canvas_size);

double CanvasToWorld(const int scalar, const double resolution);

morphac::common::aliases::Pixel WorldToCanvas(
    const morphac::common::aliases::Point& world_coord, const double resolution,
    const std::vector<int>& canvas_size);

morphac::common::aliases::Pixels WorldToCanvas(
    const morphac::common::aliases::Points& world_coords,
    const double resolution, const std::vector<int>& canvas_size);

int WorldToCanvas(const double scalar, const double resolution);

}  // namespace transforms
}  // namespace math
}  // namespace morphac

#endif
