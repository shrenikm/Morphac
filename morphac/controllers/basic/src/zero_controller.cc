#include "controllers/basic/include/zero_controller.h"

namespace morphac {
namespace controllers {
namespace basic {

using Eigen::VectorXd;

using morphac::constructs::ControlInput;

ZeroController::ZeroController(const int control_input_size)
    : Controller(), control_input_(control_input_size) {}

ZeroController::~ZeroController() {}

const ControlInput& ZeroController::Compute() { return control_input_; }

}  // namespace basic
}  // namespace controllers
}  // namespace morphac
