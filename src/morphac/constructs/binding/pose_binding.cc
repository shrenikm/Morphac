#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "constructs/include/pose.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using Eigen::VectorXd;
using morphac::constructs::Pose;

PYBIND11_MODULE(pose_binding, m) {
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

}  // namespace binding
}  // namespace constructs
}  // namespace morphac
