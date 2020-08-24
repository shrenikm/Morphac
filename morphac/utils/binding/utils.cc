#include "pybind11/pybind11.h"

#include "utils/binding/include/angle_utils_binding.h"
#include "utils/binding/include/geometry_utils_binding.h"
#include "utils/binding/include/integrator_utils_binding.h"
#include "utils/binding/include/numeric_utils_binding.h"
#include "utils/binding/include/transforms_utils_binding.h"

namespace morphac {
namespace utils {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_utils_python, m) {
  define_angle_utils_binding(m);
  define_geometry_utils_binding(m);
  define_integrator_utils_binding(m);
  define_numeric_utils_binding(m);
  define_transforms_utils_binding(m);
}

}  // namespace binding
}  // namespace utils
}  // namespace morphac
