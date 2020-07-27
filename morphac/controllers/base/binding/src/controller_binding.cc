#include "controllers/base/binding/include/controller_binding.h"

namespace morphac {
namespace controllers {
namespace base {
namespace binding {

namespace py = pybind11;

using morphac::controllers::base::Controller;

void define_controller_binding(py::module& m) {
  py::class_<Controller, PyController> controller(m, "Controller");

  controller.def(py::init<>());
}

}  // binding
}  // base
}  // controllers
}  // morphac
