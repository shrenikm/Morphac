#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "constructs/include/pose.h"

namespace morphac {
namespace constructs {
namespace bindings {

namespace py = pybind11;

using Eigen::VectorXd;
using morphac::constructs::Pose;

PYBIND11_MODULE(binding_pose, m) {
  py::class_<Pose>(m, "Pose")
      .def(py::init<const int>())
      .def(py::init<const VectorXd&>())
      .def(py::self += py::self)
      .def(py::self + py::self)
      .def(py::self -= py::self)
      .def(py::self - py::self)
      .def(py::self *= double())
      .def(py::self * double())
      .def(double() * py::self)
      .def("__getitem__",
           [](const Pose& pose, const int index) {
             return pose.get_pose_vector()(index);
           },
           py::is_operator(), py::return_value_policy::reference)
      .def("get_size", &Pose::get_size)
      .def("get_pose_vector", &Pose::get_pose_vector)
      .def("set_pose_vector", &Pose::set_pose_vector)
      .def("is_empty", &Pose::IsEmpty)
      .def("create_like", &Pose::CreateLike);
}

}  // namespace bindings
}  // namespace constructs
}  // namespace morphac
