#include "constructs/binding/include/velocity_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using Eigen::VectorXd;

using morphac::constructs::Velocity;

void define_velocity_binding(py::module& m) {
  py::class_<Velocity> velocity(m, "Velocity");

  // We don't wrap the initializer_list constructor as we can use a list to
  // Call the VectorXd constructor from python anyway.
  velocity.def(py::init<const int>(), py::arg("size"));
  velocity.def(py::init<const VectorXd&>(), py::arg("data"));
  velocity.def("__getitem__",
               [](const Velocity& velocity, const int index) {
                 // Implementing python's negative indexing.
                 if (index >= 0) {
                   return velocity[index];
                 } else {
                   return velocity[index + velocity.get_size()];
                 }
               },
               py::is_operator());
  velocity.def("__setitem__",
               [](Velocity& velocity, const int index, const double scalar) {
                 // Implementing python's negative indexing.
                 if (index >= 0) {
                   velocity[index] = scalar;
                 } else {
                   velocity[index + velocity.get_size()] = scalar;
                 }
               },
               py::is_operator());
  velocity.def(py::self += py::self);
  velocity.def(py::self + py::self);
  velocity.def(py::self -= py::self);
  velocity.def(py::self - py::self);
  velocity.def(py::self *= double());
  velocity.def(py::self * double());
  velocity.def(double() * py::self);
  velocity.def(py::self == py::self);
  velocity.def(py::self != py::self);
  velocity.def("__repr__", &Velocity::ToString);
  velocity.def_property_readonly("size", &Velocity::get_size);
  velocity.def_property(
      "data", &Velocity::get_data,
      py::overload_cast<const VectorXd&>(&Velocity::set_data));
  velocity.def("is_empty", &Velocity::IsEmpty);
  velocity.def("create_like", &Velocity::CreateLike);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

