#ifndef EIGEN_ALIASES_H
#define EIGEN_ALIASES_H

#include "Eigen/Dense"

namespace morphac {
namespace common {
namespace aliases {

using Points = Eigen::Matrix<double, Eigen::Dynamic, 2>;
using HomogeneousPoints = Eigen::Matrix<double, Eigen::Dynamic, 3>;

}  // namespace aliases
}  // namespace common
}  // namespace morphac

#endif

