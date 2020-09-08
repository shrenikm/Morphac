#include "controllers/basic/binding/include/constant_controller_binding.h"

namespace morphac {
namespace controllers {
namespace basic {
namespace binding {

namespace py = pybind11;

using Eigen::VectorXd;

using morphac::controllers::basic::ConstantController;

void define_constant_controller_binding(py::module& m) {
  py::class_<ConstantController> constant_controller(m, "ConstantController");

  constant_controller.def(py::init<const VectorXd&>(),
                          py::arg("control_input_data"));
  constant_controller.def("compute", &ConstantController::Compute);
}

}  // namespace binding
}  // namespace basic
}  // namespace controllers
}  // namespace morphac
