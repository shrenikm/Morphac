#include "mechanics/models/binding/include/diffdrive_model_binding.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

using std::string;

using morphac::mechanics::models::DiffDriveModel;
using morphac::mechanics::models::KinematicModel;

void define_diffdrive_model_binding(py::module& m) {
  py::class_<DiffDriveModel, KinematicModel> diffdrive_model(m,
                                                             "DiffDriveModel");
  diffdrive_model.def(py::init<const string, const double, const double>(),
                      py::arg("name"), py::arg("radius"), py::arg("length"));
  diffdrive_model.def("compute_state_derivative",
                      &DiffDriveModel::ComputeStateDerivative);
  diffdrive_model.def_readonly("name", &DiffDriveModel::name);
  diffdrive_model.def_readonly("radius", &DiffDriveModel::radius);
  diffdrive_model.def_readonly("length", &DiffDriveModel::length);
  diffdrive_model.def_readonly("size_pose", &KinematicModel::size_pose);
  diffdrive_model.def_readonly("size_velocity", &KinematicModel::size_velocity);
  diffdrive_model.def_readonly("size_input", &KinematicModel::size_input);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
