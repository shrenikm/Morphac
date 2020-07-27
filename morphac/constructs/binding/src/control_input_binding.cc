#include "constructs/binding/include/control_input_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using Eigen::VectorXd;
using morphac::constructs::ControlInput;

void define_control_input_binding(py::module& m) {
  py::class_<ControlInput> control_input(m, "ControlInput");

  // We don't wrap the initializer_list constructor as we can use a list to
  // Call the VectorXd constructor from python anyway.
  control_input.def(py::init<const int>(), py::arg("size"));
  control_input.def(py::init<const VectorXd&>(), py::arg("data"));
  control_input.def("__getitem__",
                    [](const ControlInput& control_input, const int index) {
                      // Implementing python's negative indexing.
                      if (index >= 0) {
                        return control_input[index];
                      } else {
                        return control_input[index + control_input.get_size()];
                      }
                    },
                    py::is_operator());
  control_input.def(
      "__setitem__",
      [](ControlInput& control_input, const int index, const double scalar) {
        // Implementing python's negative indexing.
        if (index >= 0) {
          control_input[index] = scalar;
        } else {
          control_input[index + control_input.get_size()] = scalar;
        }
      },
      py::is_operator());
  control_input.def(py::self += py::self);
  control_input.def(py::self + py::self);
  control_input.def(py::self -= py::self);
  control_input.def(py::self - py::self);
  control_input.def(py::self *= double());
  control_input.def(py::self * double());
  control_input.def(double() * py::self);
  control_input.def(py::self == py::self);
  control_input.def(py::self != py::self);
  control_input.def("__repr__", &ControlInput::ToString);
  control_input.def_property_readonly("size", &ControlInput::get_size);
  control_input.def_property(
      "data", &ControlInput::get_data,
      py::overload_cast<const VectorXd&>(&ControlInput::set_data));
  control_input.def("is_empty", &ControlInput::IsEmpty);
  control_input.def("create_like", &ControlInput::CreateLike);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

