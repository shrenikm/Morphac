#include "constructs/binding/include/state_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using Eigen::VectorXd;
using morphac::constructs::Pose;
using morphac::constructs::Velocity;
using morphac::constructs::State;

void define_state_binding(py::module& m) {
  py::class_<State> state(m, "State");

  state.def(py::init<const int, const int>(), py::arg("size_pose"),
            py::arg("size_velocity"));
  state.def(py::init<const VectorXd&, const VectorXd&>(), py::arg("data_pose"),
            py::arg("data_velocity"));
  state.def(py::init<const Pose&, const Velocity&>(), py::arg("pose"),
            py::arg("velocity"));
  state.def(py::self += py::self);
  state.def(py::self + py::self);
  state.def(py::self -= py::self);
  state.def(py::self - py::self);
  state.def(py::self *= double());
  state.def(py::self * double());
  state.def(double() * py::self);
  state.def("__repr__", &State::ToString);
  // Pose and Velocity size are not exposed as we can always call it using
  // state.pose.size and state.velocity.size
  state.def_property_readonly("size", &State::get_size);

  state.def_property("pose", py::overload_cast<>(&State::get_pose),
                     &State::set_pose);
  state.def_property("velocity", py::overload_cast<>(&State::get_velocity),
                     &State::set_velocity);

  // vector is mapped to data in python to keep it consistent and pythonic.
  // Pose and Velocity data are not exposed as we can always call it using
  // state.pose.data and state.velocity.data
  state.def_property("data", &State::get_state_vector,
                     &State::set_state_vector);
  // Pose and Velocity IsEmpty is not exposed as we can call it using
  // state.pose.is_empty and state.velocity.is_empty
  state.def("is_empty", &State::IsEmpty);
  state.def("create_like", &State::CreateLike);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

