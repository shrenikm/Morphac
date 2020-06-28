#include "constructs/binding/include/pose_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using Eigen::VectorXd;
using morphac::constructs::Pose;

void define_pose_binding(py::module& m) {
  py::class_<Pose> pose(m, "Pose");

  // We don't wrap the initializer_list constructor as we can use a list to
  // Call the VectorXd constructor from python anyway.
  pose.def(py::init<const int>(), py::arg("size"));
  pose.def(py::init<const VectorXd&>(), py::arg("data"));
  pose.def(py::self += py::self);
  pose.def(py::self + py::self);
  pose.def(py::self -= py::self);
  pose.def(py::self - py::self);
  pose.def(py::self *= double());
  pose.def(py::self * double());
  pose.def(double() * py::self);
  pose.def(py::self == py::self);
  pose.def(py::self != py::self);
  pose.def("__repr__", &Pose::ToString);
  pose.def_property_readonly("size", &Pose::get_size);
  pose.def_property("data", &Pose::get_data,
                    py::overload_cast<const VectorXd&>(&Pose::set_data));
  pose.def("is_empty", &Pose::IsEmpty);
  pose.def("create_like", &Pose::CreateLike);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

