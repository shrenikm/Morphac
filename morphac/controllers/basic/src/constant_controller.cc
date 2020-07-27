#include "controllers/basic/include/constant_controller.h"

namespace morphac {
namespace controllers {
namespace basic {

using Eigen::VectorXd;

using morphac::constructs::ControlInput;

ConstantController::ConstantController(const VectorXd& control_input_data)
    : Controller(), control_input_(control_input_data) {}

ConstantController::~ConstantController() {}

const ControlInput& ConstantController::Compute() { return control_input_; }

}  // namespace basic
}  // namespace controllers
}  // namespace morphac
