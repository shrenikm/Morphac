#include "robot/blueprint/include/footprint.h"

namespace morphac {
namespace robot {
namespace blueprint {

using Eigen::MatrixXd;

Footprint::Footprint(const MatrixXd& footprint_matrix)
    : footprint_matrix_(footprint_matrix) {
  MORPH_REQUIRE(footprint_matrix.rows() > 0 && footprint_matrix.cols() == 2,
                std::invalid_argument,
                "Invalid footprint matrix dimensions. Must be n x 2.");
}

const MatrixXd& Footprint::get_footprint_matrix() const {
  return footprint_matrix_;
}

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

