#include "constructs/binding/include/trajectory_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

using std::vector;

using Eigen::MatrixXd;
using morphac::constructs::State;
using morphac::constructs::Trajectory;

void define_trajectory_binding(py::module& m) {
  py::class_<Trajectory> trajectory(m, "Trajectory");

  trajectory.def(py::init<const State&>(), py::arg("knot_point"));
  trajectory.def(py::init<const vector<State>&>(), py::arg("knot_points"));
  trajectory.def(py::init<const MatrixXd&, const int, const int>(),
                 py::arg("data"), py::arg("pose_size"),
                 py::arg("velocity_size"));
  trajectory.def("__getitem__",
                 [](const Trajectory& trajectory, const int index) {
                   return trajectory(index);
                 },
                 py::is_operator());
  trajectory.def(
      "__setitem__",
      [](Trajectory& trajectory, const int index, const State& knot_point) {
        trajectory(index) = knot_point;
      },
      py::is_operator());
  trajectory.def(py::self += py::self);
  trajectory.def(py::self + py::self);
  trajectory.def(py::self == py::self);
  trajectory.def(py::self != py::self);
  trajectory.def("__repr__", &Trajectory::ToString);
  trajectory.def_property_readonly("dim", &Trajectory::get_dim);
  trajectory.def_property_readonly("size", &Trajectory::get_size);
  trajectory.def_property_readonly("pose_size", &Trajectory::get_pose_size);
  trajectory.def_property_readonly("velocity_size",
                                   &Trajectory::get_velocity_size);
  trajectory.def_property("data", &Trajectory::get_data, &Trajectory::set_data);
  trajectory.def("add_knot_point", py::overload_cast<const State&, const int>(
                                       &Trajectory::AddKnotPoint),
                 py::arg("knot_point"), py::arg("index"));
  trajectory.def("add_knot_point",
                 py::overload_cast<const State&>(&Trajectory::AddKnotPoint),
                 py::arg("knot_point"));
  trajectory.def("add_knot_points",
                 py::overload_cast<const vector<State>&, vector<int>>(
                     &Trajectory::AddKnotPoints),
                 py::arg("knot_points"), py::arg("indices"));
  trajectory.def("remove_knot_point",
                 py::overload_cast<const int>(&Trajectory::RemoveKnotPoint),
                 py::arg("index"));
  trajectory.def("remove_knot_point",
                 py::overload_cast<>(&Trajectory::RemoveKnotPoint));
  trajectory.def("remove_knot_points",
                 py::overload_cast<vector<int>>(&Trajectory::RemoveKnotPoints),
                 py::arg("indices"));
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

