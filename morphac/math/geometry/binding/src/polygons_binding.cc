#include "math/geometry/binding/include/polygons_binding.h"

namespace morphac {
namespace math {
namespace geometry {
namespace binding {

namespace py = pybind11;

using morphac::common::aliases::Point;
using morphac::math::geometry::ArcShape;
using morphac::math::geometry::CircleShape;
using morphac::math::geometry::CreateArc;
using morphac::math::geometry::CreateCircularPolygon;
using morphac::math::geometry::CreateRectangularPolygon;
using morphac::math::geometry::CreateRoundedRectangularPolygon;
using morphac::math::geometry::CreateTriangularPolygon;
using morphac::math::geometry::RectangleShape;
using morphac::math::geometry::RoundedRectangleShape;
using morphac::math::geometry::TriangleShape;

void define_polygons_binding(py::module& m) {
  m.def("create_arc", &CreateArc, py::arg("arc_shape"),
        py::arg("angular_resolution"));
  m.def("create_circular_polygon", &CreateCircularPolygon,
        py::arg("circle_shape"), py::arg("angular_resolution"));
  m.def("create_rectangular_polygon", &CreateRectangularPolygon,
        py::arg("rectangle_shape"));
  m.def("create_rounded_rectangular_polygon", &CreateRoundedRectangularPolygon,
        py::arg("rounded_rectangle_shape"), py::arg("angular_resolution"));
  m.def("create_triangular_polygon", &CreateTriangularPolygon,
        py::arg("triangle_shape"));
}

}  // namespace binding
}  // namespace geometry
}  // namespace math
}  // namespace morphac
