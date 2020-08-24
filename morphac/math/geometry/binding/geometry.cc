#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "math/geometry/binding/include/lines_binding.h"

namespace morphac {
namespace math {
namespace geometry {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_geometry_python, m) {
  define_lines_binding(m);
}


}  // namespace binding
}  // namespace geometry
}  // namespace math
}  // namespace morphac