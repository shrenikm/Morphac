#include "math/geometry/binding/include/lines_binding.h"
#include "math/geometry/binding/include/polygons_binding.h"
#include "math/geometry/binding/include/shapes_binding.h"
#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

namespace morphac {
namespace math {
namespace geometry {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_geometry_python, m) {
  define_lines_binding(m);
  define_polygons_binding(m);
  define_shapes_binding(m);
}

}  // namespace binding
}  // namespace geometry
}  // namespace math
}  // namespace morphac
