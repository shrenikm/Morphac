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
                     &TricycleModel::ComputeStateDerivative);
  tricycle_model.def_readonly("radius", &TricycleModel::radius);
  tricycle_model.def_readonly("length", &TricycleModel::length);
  tricycle_model.def_readonly("size_pose", &KinematicModel::size_pose);
  tricycle_model.def_readonly("size_velocity", &KinematicModel::size_velocity);
  tricycle_model.def_readonly("size_input", &KinematicModel::size_input);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
