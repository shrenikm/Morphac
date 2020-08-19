#include "utils/binding/include/angle_utils_binding.h"

namespace morphac {
namespace utils {
namespace binding {

namespace py = pybind11;

using morphac::utils::ToDegrees;
using morphac::utils::ToRadians;
using morphac::utils::NormalizeAngle;

void define_angle_utils_binding(py::module& m) {
  m.def("to_degrees", &ToDegrees, py::arg("angle"));
  m.def("to_radians", &ToRadians, py::arg("angle"));
  m.def("normalize_angle", &NormalizeAngle, py::arg("angle"));
}

}  // namespace binding
}  // namespace utils
}  // namespace morphac
