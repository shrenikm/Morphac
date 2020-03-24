#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "constructs/include/control_input.h"
#include "constructs/include/coordinate2D.h"
#include "constructs/include/pose.h"
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

PYBIND11_MODULE(_binding_constructs, m) {
  py::class_<Coordinate2D<int>> coordinate2D_int(m, "Coordinate2D");
  coordinate2D_int.def(py::init<const int, const int>());
  coordinate2D_int.def(py::self += py::self);
  coordinate2D_int.def(py::self + py::self);
  coordinate2D_int.def(py::self -= py::self);
  coordinate2D_int.def(py::self - py::self);
  coordinate2D_int.def(py::self *= int());
  coordinate2D_int.def(py::self * int());
  coordinate2D_int.def(int() * py::self);
  coordinate2D_int.def(py::self == py::self);
  coordinate2D_int.def(py::self != py::self);
  coordinate2D_int.def(py::self < py::self);
  coordinate2D_int.def(py::self > py::self);
  coordinate2D_int.def(py::self <= py::self);
  coordinate2D_int.def(py::self >= py::self);
  coordinate2D_int.def("__repr__", &Coordinate2D<int>::ToString);
  coordinate2D_int.def_property("x", &Coordinate2D<int>::get_x,
                                &Coordinate2D<int>::set_x);
  coordinate2D_int.def_property("y", &Coordinate2D<int>::get_y,
                                &Coordinate2D<int>::set_y);
  coordinate2D_int.def("set_coordinate", &Coordinate2D<int>::set_coordinate);

  py::class_<Coordinate2D<double>> coordinate2D_double(m, "Coordinate2D");
  coordinate2D_double.def(py::init<const double, const double>());
  coordinate2D_double.def(py::self += py::self);
  coordinate2D_double.def(py::self + py::self);
  coordinate2D_double.def(py::self -= py::self);
  coordinate2D_double.def(py::self - py::self);
  coordinate2D_double.def(py::self *= double());
  coordinate2D_double.def(py::self * double());
  coordinate2D_double.def(double() * py::self);
  coordinate2D_double.def(py::self == py::self);
  coordinate2D_double.def(py::self != py::self);
  coordinate2D_double.def(py::self < py::self);
  coordinate2D_double.def(py::self > py::self);
  coordinate2D_double.def(py::self <= py::self);
  coordinate2D_double.def(py::self >= py::self);
  coordinate2D_double.def("__repr__", &Coordinate2D<double>::ToString);
  coordinate2D_double.def_property("x", &Coordinate2D<double>::get_x,
                                   &Coordinate2D<double>::set_x);
  coordinate2D_double.def_property("y", &Coordinate2D<double>::get_y,
                                   &Coordinate2D<double>::set_y);
  coordinate2D_double.def("set_coordinate",
                          &Coordinate2D<double>::set_coordinate);

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
