#include "controllers/basic/binding/include/zero_controller_binding.h"

namespace morphac {
namespace controllers {
namespace basic {
namespace binding {

namespace py = pybind11;

using morphac::controllers::basic::ZeroController;

void define_zero_controller_binding(py::module& m) {
  py::class_<ZeroController> zero_controller(m, "ZeroController");

  zero_controller.def(py::init<const int>(), py::arg("control_input_size"));
  zero_controller.def("compute", &ZeroController::Compute);
}

}  // binding
}  // basic
}  // controllers
}  // morphac
