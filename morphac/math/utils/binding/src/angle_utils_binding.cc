#include "math/utils/binding/include/angle_utils_binding.h"

namespace morphac {
namespace math {
namespace utils {
namespace binding {

namespace py = pybind11;

using morphac::math::utils::ToDegrees;
using morphac::math::utils::ToRadians;
using morphac::math::utils::NormalizeAngle;

void define_angle_utils_binding(py::module& m) {
  m.def("to_degrees", &ToDegrees);
  m.def("to_radians", &ToRadians);
  m.def("normalize_angle", &NormalizeAngle);
}


}  // namespace binding
}  // namespace utils
}  // namespace math
}  // namespace morphac
