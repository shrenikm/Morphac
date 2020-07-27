#include "utils/binding/include/integrator_utils_binding.h"

namespace morphac {
namespace utils {
namespace binding {

namespace py = pybind11;

using morphac::utils::IntegratorFromType;

void define_integrator_utils_binding(py::module& m) {
  m.def("integrator_from_type", &IntegratorFromType, py::arg("integrator_type"),
        py::arg("kinematic_model"));
}

}  // namespace binding
}  // namespace utils
}  // namespace morphac
