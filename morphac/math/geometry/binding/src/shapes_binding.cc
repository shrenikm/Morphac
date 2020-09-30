#include "math/geometry/binding/include/shapes_binding.h"

namespace morphac {
namespace math {
namespace geometry {
namespace binding {

namespace py = pybind11;

using morphac::common::aliases::Point;
using morphac::math::geometry::ArcShape;
using morphac::math::geometry::CircleShape;
using morphac::math::geometry::RectangleShape;
using morphac::math::geometry::RoundedRectangleShape;
using morphac::math::geometry::TriangleShape;

void define_shapes_binding(py::module& m) {
  py::class_<ArcShape> arc_shape(m, "ArcShape");
  arc_shape.def(
      py::init<const Point, const double, const double, const double>(),
      py::arg("center"), py::arg("start_angle"), py::arg("end_angle"),
      py::arg("radius"));
  arc_shape.def_readonly("center", &ArcShape::center);
  arc_shape.def_readonly("start_angle", &ArcShape::start_angle);
  arc_shape.def_readonly("end_angle", &ArcShape::end_angle);
  arc_shape.def_readonly("radius", &ArcShape::radius);

  py::class_<CircleShape> circle_shape(m, "CircleShape");
  circle_shape.def(py::init<const Point, const double>(), py::arg("center"),
                   py::arg("radius"));
  circle_shape.def_readonly("center", &CircleShape::center);
  circle_shape.def_readonly("radius", &CircleShape::radius);

  py::class_<RectangleShape> rectangle_shape(m, "RectangleShape");
  rectangle_shape.def(
      py::init<const Point, const double, const double, const double>(),
      py::arg("center"), py::arg("size_x"), py::arg("size_y"),
      py::arg("angle"));
  rectangle_shape.def_readonly("center", &RectangleShape::center);
  rectangle_shape.def_readonly("size_x", &RectangleShape::size_x);
  rectangle_shape.def_readonly("size_y", &RectangleShape::size_y);
  rectangle_shape.def_readonly("angle", &RectangleShape::angle);

  py::class_<RoundedRectangleShape> rounded_rectangle_shape(
      m, "RoundedRectangleShape");
  rounded_rectangle_shape.def(py::init<const Point, const double, const double,
                                       const double, const double>(),
                              py::arg("center"), py::arg("size_x"),
                              py::arg("size_y"), py::arg("angle"),
                              py::arg("radius"));
  rounded_rectangle_shape.def_readonly("center",
                                       &RoundedRectangleShape::center);
  rounded_rectangle_shape.def_readonly("size_x",
                                       &RoundedRectangleShape::size_x);
  rounded_rectangle_shape.def_readonly("size_y",
                                       &RoundedRectangleShape::size_y);
  rounded_rectangle_shape.def_readonly("angle", &RoundedRectangleShape::angle);
  rounded_rectangle_shape.def_readonly("radius",
                                       &RoundedRectangleShape::radius);

  py::class_<TriangleShape> triangle_shape(m, "TriangleShape");
  triangle_shape.def(
      py::init<const Point, const double, const double, const double>(),
      py::arg("center"), py::arg("base"), py::arg("height"), py::arg("angle"));
  triangle_shape.def_readonly("center", &TriangleShape::center);
  triangle_shape.def_readonly("base", &TriangleShape::base);
  triangle_shape.def_readonly("height", &TriangleShape::height);
  triangle_shape.def_readonly("angle", &TriangleShape::angle);
}

}  // namespace binding
}  // namespace geometry
}  // namespace math
}  // namespace morphac
