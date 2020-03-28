#include "constructs/binding/include/control_input_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using Eigen::VectorXd;
using morphac::constructs::ControlInput;

void define_control_input_binding(py::module& m) {
  py::class_<ControlInput> input(m, "ControlInput");
  input.def(py::init<const int>());
  input.def(py::init<const VectorXd&>());
  input.def(py::self += py::self);
  input.def(py::self + py::self);
  input.def(py::self -= py::self);
  input.def(py::self - py::self);
  input.def(py::self *= double());
  input.def(py::self * double());
  input.def(double() * py::self);
  input.def("__repr__", &ControlInput::ToString);
  input.def_property_readonly("size", &ControlInput::get_size);
  input.def_property("data", &ControlInput::get_input_vector,
                     &ControlInput::set_input_vector);
  input.def("is_empty", &ControlInput::IsEmpty);
  input.def("create_like", &ControlInput::CreateLike);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

