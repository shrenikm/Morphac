#include "utils/binding/include/geometry_utils_binding.h"

namespace morphac {
namespace utils {
namespace binding {

namespace py = pybind11;

using morphac::utils::CreateArc;
using morphac::utils::CreateCircularPolygon;
using morphac::utils::CreateRectangularPolygon;
using morphac::utils::CreateRoundedRectangularPolygon;

void define_geometry_utils_binding(py::module& m) {
  m.def("create_arc", CreateArc, py::arg("start_angle"), py::arg("end_angle"),
        py::arg("radius"), py::arg("angular_resolution"), py::arg("center"));
}

}  // namespace binding
}  // namespace utils
}  // namespace morphac

