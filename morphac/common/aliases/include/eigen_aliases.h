#ifndef EIGEN_ALIASES_H
#define EIGEN_ALIASES_H

#include "Eigen/Dense"

namespace morphac {
namespace common {
namespace aliases {

using Pixel = Eigen::Matrix<int, 2, 1>;
using Pixels = Eigen::Matrix<int, Eigen::Dynamic, 2>;
using Point = Eigen::Matrix<double, 2, 1>;
using Points = Eigen::Matrix<double, Eigen::Dynamic, 2>;
// The order of the bounding box points are top left, top right, bottom right
// and bottom left.
using BoundingBox = Eigen::Matrix<double, 4, 2>;
using HomogeneousPoint = Eigen::Matrix<double, 3, 1>;
using HomogeneousPoints = Eigen::Matrix<double, Eigen::Dynamic, 3>;
using MapData =
    Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

}  // namespace aliases
}  // namespace common
}  // namespace morphac

#endif
