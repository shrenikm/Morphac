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

  // We don't wrap the initializer_list constructor as we can use a list to
  // Call the VectorXd constructor from python anyway.
  state.def(py::init<const int, const int>(), py::arg("pose_size"),
            py::arg("velocity_size"));
  state.def(py::init<const VectorXd&, const VectorXd&>(), py::arg("data_pose"),
            py::arg("data_velocity"));
  state.def(py::init<const Pose&, const Velocity&>(), py::arg("pose"),
            py::arg("velocity"));
  state.def("__getitem__",
            [](const State& state, const int index) {
              // Implementing python's negative indexing.
              if (index >= 0) {
                return state[index];
              } else {
                return state[index + state.get_size()];
              }
            },
            py::is_operator());
  state.def("__setitem__",
            [](State& state, const int index, const double scalar) {
              // Implementing python's negative indexing.
              if (index >= 0) {
                state[index] = scalar;
              } else {
                state[index + state.get_size()] = scalar;
              }
            },
            py::is_operator());
  state.def(py::self += py::self);
  state.def(py::self + py::self);
  state.def(py::self -= py::self);
  state.def(py::self - py::self);
  state.def(py::self *= double());
  state.def(py::self * double());
  state.def(double() * py::self);
  state.def(py::self == py::self);
  state.def(py::self != py::self);
  state.def("__repr__", &State::ToString);
  state.def_property_readonly("size", &State::get_size);
  state.def_property_readonly("pose_size", &State::get_pose_size);
  state.def_property_readonly("velocity_size", &State::get_velocity_size);
  state.def_property("pose", py::overload_cast<>(&State::get_pose),
                     &State::set_pose);
  state.def_property("velocity", py::overload_cast<>(&State::get_velocity),
                     &State::set_velocity);
  // Pose and Velocity data are not exposed as we can always call it using
  // state.pose.data and state.velocity.data
  state.def_property("data", &State::get_data,
                     py::overload_cast<const VectorXd&>(&State::set_data));
  // Pose and Velocity IsEmpty is not exposed as we can call it using
  // state.pose.is_empty and state.velocity.is_empty
  state.def("is_empty", &State::IsEmpty);
  state.def("is_pose_empty", &State::IsPoseEmpty);
  state.def("is_velocity_empty", &State::IsVelocityEmpty);
  state.def("create_like", &State::CreateLike);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

