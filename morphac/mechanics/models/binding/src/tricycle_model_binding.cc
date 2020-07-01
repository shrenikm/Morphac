#include "mechanics/models/binding/include/tricycle_model_binding.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

using morphac::mechanics::models::TricycleModel;
using morphac::mechanics::models::KinematicModel;

void define_tricycle_model_binding(py::module& m) {
  py::class_<TricycleModel, KinematicModel> tricycle_model(m, "TricycleModel");

  tricycle_model.def(py::init<const double, const double>(), py::arg("radius"),
                     py::arg("length"));
  tricycle_model.def("compute_state_derivative",
                     &TricycleModel::ComputeStateDerivative,
                     py::arg("robot_state"), py::arg("robot_input"));
  tricycle_model.def("normalize_state", &TricycleModel::NormalizeState);
  tricycle_model.def_readonly("radius", &TricycleModel::radius);
  tricycle_model.def_readonly("length", &TricycleModel::length);
  tricycle_model.def_readonly("pose_size", &KinematicModel::pose_size);
  tricycle_model.def_readonly("velocity_size", &KinematicModel::velocity_size);
  tricycle_model.def_readonly("input_size", &KinematicModel::input_size);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
