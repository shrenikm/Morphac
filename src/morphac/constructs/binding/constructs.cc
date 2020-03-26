#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "constructs/include/control_input.h"
#include "constructs/include/coordinate2D.h"
#include "constructs/include/pose.h"
#include "constructs/include/state.h"
#include "constructs/include/velocity.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using Eigen::VectorXd;
using morphac::constructs::Coordinate2D;
using morphac::constructs::ControlInput;
using morphac::constructs::Pose;
using morphac::constructs::Velocity;
using morphac::constructs::State;

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

void define_pose_binding(py::module& m) {
  py::class_<Pose> pose(m, "Pose");
  pose.def(py::init<const int>());
  pose.def(py::init<const VectorXd&>());
  pose.def(py::self += py::self);
  pose.def(py::self + py::self);
  pose.def(py::self -= py::self);
  pose.def(py::self - py::self);
  pose.def(py::self *= double());
  pose.def(py::self * double());
  pose.def(double() * py::self);
  pose.def("__repr__", &Pose::ToString);
  pose.def_property_readonly("size", &Pose::get_size);
  pose.def_property("data", &Pose::get_pose_vector, &Pose::set_pose_vector);
  pose.def("is_empty", &Pose::IsEmpty);
  pose.def("create_like", &Pose::CreateLike);
}

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

void define_state_binding(py::module& m) {
  py::class_<State> state(m, "State");
  state.def(py::init<const int, const int>());
  state.def(py::init<const VectorXd&, const VectorXd&>());
  state.def(py::init<const Pose&, const Velocity&>());
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

  state.def_property_readonly("pose", py::overload_cast<>(&State::get_pose));
  state.def_property_readonly("velocity",
                              py::overload_cast<>(&State::get_velocity));

  // Pose and Velocity data are not exposed as we can always call it using
  // state.pose.data and state.velocity.data
  state.def_property("data", &State::get_state_vector,
                     &State::set_state_vector);
  // Pose and Velocity IsEmpty is not exposed as we can call it using
  // state.pose.is_empty and state.velocity.is_empty
  state.def("is_empty", &State::IsEmpty);
  state.def("create_like", &State::CreateLike);
}

PYBIND11_MODULE(_binding_constructs, m) {
  define_coordinate2D_binding(m);
  define_control_input_binding(m);
  define_pose_binding(m);
  define_velocity_binding(m);
  define_state_binding(m);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac
