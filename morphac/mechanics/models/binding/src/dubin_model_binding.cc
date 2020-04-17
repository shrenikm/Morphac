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
                  &DubinModel::ComputeStateDerivative);
  dubin_model.def_readonly("speed", &DubinModel::speed);
  dubin_model.def_readonly("size_pose", &KinematicModel::size_pose);
  dubin_model.def_readonly("size_velocity", &KinematicModel::size_velocity);
  dubin_model.def_readonly("size_input", &KinematicModel::size_input);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
