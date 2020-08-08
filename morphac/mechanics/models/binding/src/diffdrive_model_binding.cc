#include "mechanics/models/binding/include/diffdrive_model_binding.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

using morphac::mechanics::models::DiffDriveModel;
using morphac::mechanics::models::KinematicModel;

void define_diffdrive_model_binding(py::module& m) {
  py::class_<DiffDriveModel, KinematicModel> diffdrive_model(m,
                                                             "DiffDriveModel");

  diffdrive_model.def(py::init<const double, const double>(), py::arg("radius"),
                      py::arg("length"));
  diffdrive_model.def("compute_state_derivative",
                      &DiffDriveModel::ComputeStateDerivative,
                      py::arg("robot_state"), py::arg("control_input"));
  diffdrive_model.def("normalize_state", &DiffDriveModel::NormalizeState,
                      py::arg("robot_state"));
  diffdrive_model.def_readonly("radius", &DiffDriveModel::radius);
  diffdrive_model.def_readonly("length", &DiffDriveModel::length);
  diffdrive_model.def_readonly("pose_size", &KinematicModel::pose_size);
  diffdrive_model.def_readonly("velocity_size", &KinematicModel::velocity_size);
  diffdrive_model.def_readonly("control_input_size",
                               &KinematicModel::control_input_size);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
