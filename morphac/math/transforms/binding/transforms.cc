#include "math/transforms/binding/include/transforms_binding.h"
#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

namespace morphac {
namespace math {
namespace transforms {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_transforms_python, m) { define_transforms_binding(m); }

}  // namespace binding
}  // namespace transforms
}  // namespace math
}  // namespace morphac
