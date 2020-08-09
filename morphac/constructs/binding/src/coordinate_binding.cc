#include "constructs/binding/include/coordinate_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using morphac::constructs::Coordinate;

void define_coordinate_binding(py::module& m) {
  py::class_<Coordinate<double>> coordinate(m, "Coordinate");

  coordinate.def(py::init<const double, const double>(), py::arg("x"),
                 py::arg("y"));
  coordinate.def("__getitem__",
                 [](const Coordinate<double>& coord, const int index) {
                   // Implementing python's negative indexing.
                   if (index >= 0) {
                     return coord[index];
                   } else {
                     return coord[index + 2];
                   }
                 },
                 py::is_operator());
  coordinate.def(
      "__setitem__",
      [](Coordinate<double>& coord, const int index, const double scalar) {
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
  coordinate.def("__repr__", &Coordinate<double>::ToString);
  coordinate.def_property("x", &Coordinate<double>::get_x,
                          &Coordinate<double>::set_x);
  coordinate.def_property("y", &Coordinate<double>::get_y,
                          &Coordinate<double>::set_y);
  coordinate.def_property("data", &Coordinate<double>::get_data,
                          &Coordinate<double>::set_data);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

