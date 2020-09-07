#include "mechanics/models/binding/include/diffdrive_model_binding.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

using morphac::mechanics::models::DiffdriveModel;
using morphac::mechanics::models::KinematicModel;

void define_diffdrive_model_binding(py::module& m) {
  py::class_<DiffdriveModel, KinematicModel> diffdrive_model(m,
                                                             "DiffdriveModel");

  diffdrive_model.def(py::init<const double, const double>(), py::arg("radius"),
                      py::arg("width"));
  diffdrive_model.def("compute_state_derivative",
                      &DiffdriveModel::ComputeStateDerivative,
                      py::arg("robot_state"), py::arg("control_input"));
  diffdrive_model.def("normalize_state", &DiffdriveModel::NormalizeState,
                      py::arg("robot_state"));
  diffdrive_model.def("default_footprint", &DiffdriveModel::DefaultFootprint);
  diffdrive_model.def_readonly("radius", &DiffdriveModel::radius);
  diffdrive_model.def_readonly("width", &DiffdriveModel::width);
  diffdrive_model.def_readonly("pose_size", &KinematicModel::pose_size);
  diffdrive_model.def_readonly("velocity_size", &KinematicModel::velocity_size);
  diffdrive_model.def_readonly("control_input_size",
                               &KinematicModel::control_input_size);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
