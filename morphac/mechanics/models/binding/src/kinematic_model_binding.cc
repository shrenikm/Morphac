#include "mechanics/models/binding/include/kinematic_model_binding.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

using std::string;

void define_kinematic_model_binding(py::module& m) {
  py::class_<KinematicModel, PyKinematicModel> kinematic_model(
      m, "KinematicModel");
  kinematic_model.def(py::init<const string, const int, const int, const int>(),
                      py::arg("name"), py::arg("size_pose"),
                      py::arg("size_velocity"), py::arg("size_input"));
  kinematic_model.def("compute_state_derivative",
                      &KinematicModel::ComputeStateDerivative);
  kinematic_model.def_readonly("name", &KinematicModel::name);
  kinematic_model.def_readonly("size_pose", &KinematicModel::size_pose);
  kinematic_model.def_readonly("size_velocity", &KinematicModel::size_velocity);
  kinematic_model.def_readonly("size_input", &KinematicModel::size_input);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac