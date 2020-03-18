#include "pybind11/pybind11.h"
#include "pybind11/eigen.h"

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
    .def("get_size", &Pose::get_size);
}


}  // namespace bindings
}  // namespace constructs
}  // namespace morphac
