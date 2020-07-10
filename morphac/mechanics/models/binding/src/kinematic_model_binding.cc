#include "mechanics/models/binding/include/kinematic_model_binding.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

using morphac::mechanics::models::KinematicModel;

void define_kinematic_model_binding(py::module& m) {
  py::class_<KinematicModel, PyKinematicModel> kinematic_model(
      m, "KinematicModel");

  kinematic_model.def(py::init<const int, const int, const int>(),
                      py::arg("size_pose"), py::arg("size_velocity"),
                      py::arg("size_control_input"));
  kinematic_model.def("compute_state_derivative",
                      &KinematicModel::ComputeStateDerivative,
                      py::arg("robot_state"), py::arg("control_input"));
  kinematic_model.def("normalize_state", &KinematicModel::NormalizeState);
  kinematic_model.def_readonly("pose_size", &KinematicModel::pose_size);
  kinematic_model.def_readonly("velocity_size", &KinematicModel::velocity_size);
  kinematic_model.def_readonly("control_input_size",
                               &KinematicModel::control_input_size);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
