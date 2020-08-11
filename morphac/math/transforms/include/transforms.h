#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include <vector>

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

const Eigen::Vector2d CanvasToWorld(const Eigen::Vector2d& canvas_coord,
                                    const double resolution);

const morphac::constructs::Coordinate CanvasToWorld(
    const morphac::constructs::Coordinate& canvas_coord,
    const double resolution);

const Eigen::Vector2d WorldToCanvas(const Eigen::Vector2d& world_coord,
                                    const double resolution,
                                    const std::vector<int>& canvas_size = {});

const morphac::constructs::Coordinate WorldToCanvas(
    const morphac::constructs::Coordinate& world_coord, const double resolution,
    const std::vector<int>& canvas_size = {});

}  // namespace transforms
}  // namespace math
}  // namespace morphac

#endif
