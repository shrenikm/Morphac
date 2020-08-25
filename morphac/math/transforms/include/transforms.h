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
// represent all coordinates as Vector2d/Vector2i. If Coordinates are required,
// it should be easy enough to convert them to vectors in the argument and wrap
// them as Coordinates while returning.

const Eigen::MatrixXd RotationMatrix(const double angle);

const Eigen::MatrixXd TransformationMatrix(const double angle,
                                           const Eigen::Vector2d& translation);

morphac::common::aliases::Points TranslatePoints(
    const morphac::common::aliases::Points& points,
    const Eigen::Vector2d& translation);

morphac::common::aliases::Points RotatePoints(
    const morphac::common::aliases::Points& points, const double angle,
    const Eigen::Vector2d& center = Eigen::Vector2d::Zero());

morphac::common::aliases::Points TransformPoints(
    const morphac::common::aliases::Points& points, const double angle,
    const Eigen::Vector2d& translation);

morphac::common::aliases::Points CanvasToWorld(
    const morphac::common::aliases::Pixels& canvas_coords,
    const double resolution);

Eigen::Vector2d CanvasToWorld(const Eigen::Vector2i& canvas_coord,
                              const double resolution);

Eigen::Vector2i WorldToCanvas(const Eigen::Vector2d& world_coord,
                              const double resolution,
                              const std::vector<int>& canvas_size = {});

morphac::common::aliases::Pixels WorldToCanvas(
    const morphac::common::aliases::Points& world_coords,
    const double resolution, const std::vector<int>& canvas_size = {});

}  // namespace transforms
}  // namespace math
}  // namespace morphac

#endif
