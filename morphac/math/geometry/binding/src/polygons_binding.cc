#include "math/geometry/binding/include/polygons_binding.h"

namespace morphac {
namespace math {
namespace geometry {
namespace binding {

namespace py = pybind11;

using Eigen::Vector2d;

using morphac::math::geometry::CreateArc;
using morphac::math::geometry::CreateCircularPolygon;
using morphac::math::geometry::CreateRectangularPolygon;
using morphac::math::geometry::CreateRoundedRectangularPolygon;

void define_polygons_binding(py::module& m) {
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
}  // namespace geometry
}  // namespace math
}  // namespace morphac
