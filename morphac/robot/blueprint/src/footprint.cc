#include "robot/blueprint/include/footprint.h"

namespace morphac {
namespace robot {
namespace blueprint {

using Eigen::MatrixXd;

Footprint::Footprint(const MatrixXd& data) : data_(data) {
  MORPH_REQUIRE(data.rows() > 0 && data.cols() == 2, std::invalid_argument,
                "Invalid footprint matrix dimensions. Must be n x 2.");
}

const MatrixXd& Footprint::get_data() const { return data_; }

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

