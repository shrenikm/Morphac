#include "controllers/basic/include/zero_controller.h"

namespace morphac {
namespace controllers {
namespace basic {

using morphac::constructs::ControlInput;

ZeroController::ZeroController(const int control_input_size)
    : Controller(), control_input_(control_input_size) {
  MORPH_REQUIRE(control_input_size > 0, std::invalid_argument,
                "Control input size must be positive");
}

ZeroController::~ZeroController() {}

const ControlInput& ZeroController::Compute() { return control_input_; }

}  // namespace basic
}  // namespace controllers
}  // namespace morphac
