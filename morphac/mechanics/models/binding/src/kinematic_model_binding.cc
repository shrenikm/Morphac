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
                      py::arg("size_input"));
  kinematic_model.def_readonly("size_pose", &KinematicModel::size_pose);
  kinematic_model.def_readonly("size_velocity", &KinematicModel::size_velocity);
  kinematic_model.def_readonly("size_input", &KinematicModel::size_input);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
