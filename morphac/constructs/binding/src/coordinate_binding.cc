#include "constructs/binding/include/coordinate_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using Eigen::Vector2d;

using morphac::constructs::Coordinate;

void define_coordinate_binding(py::module& m) {
  py::class_<Coordinate> coordinate(m, "Coordinate");

  coordinate.def(py::init<const double, const double>(), py::arg("x") = 0.,
                 py::arg("y") = 0.);
  coordinate.def(py::init<const Vector2d&>(), py::arg("data"));
  coordinate.def("__getitem__",
                 [](const Coordinate& coord, const int index) {
                   // Implementing python's negative indexing.
                   if (index >= 0) {
                     return coord[index];
                   } else {
                     return coord[index + 2];
                   }
                 },
                 py::is_operator());
  coordinate.def("__setitem__",
                 [](Coordinate& coord, const int index, const double scalar) {
                   // Implementing python's negative indexing.
                   if (index >= 0) {
                     coord[index] = scalar;
                   } else {
                     coord[index + 2] = scalar;
                   }
                 },
                 py::is_operator());
  coordinate.def(py::self += py::self);
  coordinate.def(py::self + py::self);
  coordinate.def(py::self -= py::self);
  coordinate.def(py::self - py::self);
  coordinate.def(py::self *= double());
  coordinate.def(py::self * double());
  coordinate.def(double() * py::self);
  coordinate.def(py::self == py::self);
  coordinate.def(py::self != py::self);
  coordinate.def(py::self < py::self);
  coordinate.def(py::self > py::self);
  coordinate.def(py::self <= py::self);
  coordinate.def(py::self >= py::self);
  coordinate.def("__repr__", &Coordinate::ToString);
  coordinate.def_property("x", &Coordinate::get_x, &Coordinate::set_x);
  coordinate.def_property("y", &Coordinate::get_y, &Coordinate::set_y);
  coordinate.def_property("data", &Coordinate::get_data, &Coordinate::set_data);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

