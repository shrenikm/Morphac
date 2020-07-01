#include "mechanics/models/binding/include/dubin_model_binding.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

using morphac::mechanics::models::DubinModel;
using morphac::mechanics::models::KinematicModel;

void define_dubin_model_binding(py::module& m) {
  py::class_<DubinModel, KinematicModel> dubin_model(m, "DubinModel");

  dubin_model.def(py::init<const double>(), py::arg("speed"));
  dubin_model.def("compute_state_derivative",
                  &DubinModel::ComputeStateDerivative, py::arg("robot_state"),
                  py::arg("robot_input"));
  dubin_model.def("normalize_state", &DubinModel::NormalizeState);
  dubin_model.def_readonly("speed", &DubinModel::speed);
  dubin_model.def_readonly("pose_size", &KinematicModel::pose_size);
  dubin_model.def_readonly("velocity_size", &KinematicModel::velocity_size);
  dubin_model.def_readonly("input_size", &KinematicModel::input_size);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
