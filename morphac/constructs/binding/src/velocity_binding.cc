#include "constructs/binding/include/velocity_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using Eigen::VectorXd;
using morphac::constructs::Velocity;

void define_velocity_binding(py::module& m) {
  py::class_<Velocity> velocity(m, "Velocity");
  velocity.def(py::init<const int>());
  velocity.def(py::init<const VectorXd&>());
  velocity.def(py::self += py::self);
  velocity.def(py::self + py::self);
  velocity.def(py::self -= py::self);
  velocity.def(py::self - py::self);
  velocity.def(py::self *= double());
  velocity.def(py::self * double());
  velocity.def(double() * py::self);
  velocity.def("__repr__", &Velocity::ToString);
  velocity.def_property_readonly("size", &Velocity::get_size);
  velocity.def_property("data", &Velocity::get_velocity_vector,
                        &Velocity::set_velocity_vector);
  velocity.def("is_empty", &Velocity::IsEmpty);
  velocity.def("create_like", &Velocity::CreateLike);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

