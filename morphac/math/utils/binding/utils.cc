#include "pybind11/pybind11.h"

#include "math/utils/binding/include/angle_utils_binding.h"

namespace morphac {
namespace math {
namespace utils {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_utils, m) { define_angle_utils_binding(m); }

}  // namespace binding
}  // namespace utils
}  // namespace math
}  // namespace morphac
