#include "constructs/binding/include/input_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using Eigen::VectorXd;
using morphac::constructs::Input;

void define_input_binding(py::module& m) {
  py::class_<Input> input(m, "Input");
  input.def(py::init<const int>(), py::arg("size"));
  input.def(py::init<const VectorXd&>(), py::arg("data"));
  input.def(py::self += py::self);
  input.def(py::self + py::self);
  input.def(py::self -= py::self);
  input.def(py::self - py::self);
  input.def(py::self *= double());
  input.def(py::self * double());
  input.def(double() * py::self);
  input.def("__repr__", &Input::ToString);
  input.def_property_readonly("size", &Input::get_size);
  // vector is mapped to data in python to keep it consistent and pythonic.
  input.def_property("data", &Input::get_input_vector,
                     &Input::set_input_vector);
  input.def("is_empty", &Input::IsEmpty);
  input.def("create_like", &Input::CreateLike);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac
