#include "controllers/binding/include/controller_binding.h"

namespace morphac {
namespace controllers {
namespace binding {

namespace py = pybind11;

using morphac::controllers::Controller;

void define_controller_binding(py::module& m) {
  py::class_<Controller, PyController> controller(m, "Controller");

  controller.def(py::init<>());
}

}  // binding
}  // controllers
}  // morphac
