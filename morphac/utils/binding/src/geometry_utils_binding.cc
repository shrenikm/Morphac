#include "utils/binding/include/geometry_utils_binding.h"

namespace morphac {
namespace utils {
namespace binding {

namespace py = pybind11;

using Eigen::Vector2d;

using morphac::utils::CreateArc;
using morphac::utils::CreateCircularPolygon;
using morphac::utils::CreateRectangularPolygon;
using morphac::utils::CreateRoundedRectangularPolygon;

void define_geometry_utils_binding(py::module& m) {
  m.def("create_arc", &CreateArc, py::arg("start_angle"), py::arg("end_angle"),
        py::arg("radius"), py::arg("angular_resolution"),
        py::arg("center") = Vector2d::Zero());
  m.def("create_circular_polygon", &CreateCircularPolygon, py::arg("radius"),
        py::arg("angular_resolution"), py::arg("center") = Vector2d::Zero());
  m.def("create_rectangular_polygon", &CreateRectangularPolygon,
        py::arg("size_x"), py::arg("size_y"), py::arg("angle"),
        py::arg("center") = Vector2d::Zero());
  m.def("create_rounded_rectangular_polygon", &CreateRoundedRectangularPolygon,
        py::arg("size_x"), py::arg("size_y"), py::arg("angle"),
        py::arg("radius"), py::arg("angular_resolution"),
        py::arg("center") = Vector2d::Zero());
}

}  // namespace binding
}  // namespace utils
}  // namespace morphac

