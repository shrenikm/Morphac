#include "controllers/basic/include/constant_controller.h"

namespace morphac {
namespace controllers {
namespace basic {

using Eigen::VectorXd;

using morphac::constructs::ControlInput;

ConstantController::ConstantController(const VectorXd& control_input_data)
    : Controller(), control_input_(control_input_data) {
  MORPH_REQUIRE(control_input_data.size() > 0, std::invalid_argument,
                "Control input data must not be empty.");
}

ConstantController::~ConstantController() {}

const ControlInput& ConstantController::Compute() { return control_input_; }

}  // namespace basic
}  // namespace controllers
}  // namespace morphac
