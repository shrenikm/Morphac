#include "math/geometry/binding/include/lines_binding.h"

namespace morphac {
namespace math {
namespace geometry {
namespace binding {

namespace py = pybind11;

using morphac::common::aliases::Point;
using morphac::math::geometry::AreLinesParallel;
using morphac::math::geometry::AreLinesPerpendicular;
using morphac::math::geometry::ComputeLineSpec;
using morphac::math::geometry::LineSpec;
using morphac::math::geometry::PointProjection;

void define_lines_binding(py::module& m) {
  py::class_<LineSpec> line_spec(m, "LineSpec");

  line_spec.def(py::init<const double, const double, const double>(),
                py::arg("slope"), py::arg("x_intercept"),
                py::arg("y_intercept"));
  line_spec.def(py::self == py::self);
  line_spec.def(py::self != py::self);
  line_spec.def("__repr__", &LineSpec::ToString);
  line_spec.def_readonly("slope", &LineSpec::slope);
  line_spec.def_readonly("x_intercept", &LineSpec::x_intercept);
  line_spec.def_readonly("y_intercept", &LineSpec::y_intercept);

  py::class_<PointProjection> point_projection(m, "PointProjection");

  point_projection.def(py::init<const double, const double, const Point&>(),
                       py::arg("distance"), py::arg("alpha"),
                       py::arg("projection"));
  point_projection.def(py::init<const double, const Point&>(),
                       py::arg("distance"), py::arg("projection"));
  point_projection.def_readonly("distance", &PointProjection::distance);
  point_projection.def_readonly("alpha", &PointProjection::alpha);
  point_projection.def_readonly("projection", &PointProjection::projection);

  m.def("compute_line_spec", &ComputeLineSpec, py::arg("start_point"),
        py::arg("end_point"));

  m.def("are_lines_parallel",
        py::overload_cast<const LineSpec&, const LineSpec&>(&AreLinesParallel),
        py::arg("line_spec1"), py::arg("line_spec2"));
  m.def(
      "are_lines_parallel",
      py::overload_cast<const Point&, const Point&, const Point&, const Point&>(
          &AreLinesParallel),
      py::arg("start_point1"), py::arg("end_point1"), py::arg("start_point2"),
      py::arg("end_point2"));

  m.def("are_lines_perpendicular",
        py::overload_cast<const LineSpec&, const LineSpec&>(
            &AreLinesPerpendicular),
        py::arg("line_spec1"), py::arg("line_spec2"));
  m.def(
      "are_lines_perpendicular",
      py::overload_cast<const Point&, const Point&, const Point&, const Point&>(
          &AreLinesPerpendicular),
      py::arg("start_point1"), py::arg("end_point1"), py::arg("start_point2"),
      py::arg("end_point2"));
}

}  // namespace binding
}  // namespace geometry
}  // namespace math
}  // namespace morphac
