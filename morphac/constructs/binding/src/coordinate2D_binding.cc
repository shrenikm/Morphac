#include "constructs/binding/include/coordinate2D_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using morphac::constructs::Coordinate2D;

void define_coordinate2D_binding(py::module& m) {
  py::class_<Coordinate2D<double>> coordinate2D(m, "Coordinate2D");
  coordinate2D.def(py::init<const double, const double>());
  coordinate2D.def(py::self += py::self);
  coordinate2D.def(py::self + py::self);
  coordinate2D.def(py::self -= py::self);
  coordinate2D.def(py::self - py::self);
  coordinate2D.def(py::self *= double());
  coordinate2D.def(py::self * double());
  coordinate2D.def(double() * py::self);
  coordinate2D.def(py::self == py::self);
  coordinate2D.def(py::self != py::self);
  coordinate2D.def(py::self < py::self);
  coordinate2D.def(py::self > py::self);
  coordinate2D.def(py::self <= py::self);
  coordinate2D.def(py::self >= py::self);
  coordinate2D.def("__repr__", &Coordinate2D<double>::ToString);
  coordinate2D.def_property("x", &Coordinate2D<double>::get_x,
                            &Coordinate2D<double>::set_x);
  coordinate2D.def_property("y", &Coordinate2D<double>::get_y,
                            &Coordinate2D<double>::set_y);
  coordinate2D.def("set_coordinate", &Coordinate2D<double>::set_coordinate);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

