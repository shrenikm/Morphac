#include "mechanics/models/binding/include/ackermann_model_binding.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

using morphac::mechanics::models::AckermannModel;
using morphac::mechanics::models::KinematicModel;

void define_ackermann_model_binding(py::module& m) {
  py::class_<AckermannModel, KinematicModel> ackermann_model(m,
                                                             "AckermannModel");
  ackermann_model.def(py::init<const double, const double>(), py::arg("width"),
                      py::arg("length"));
  ackermann_model.def("compute_state_derivative",
                      &AckermannModel::ComputeStateDerivative,
                      py::arg("robot_state"), py::arg("control_input"));
  ackermann_model.def("normalized_state", &AckermannModel::NormalizeState,
                      py::arg("robot_state"));
  ackermann_model.def("compute_inner_steering_angle",
                      &AckermannModel::ComputeInnerSteeringAngle,
                      py::arg("ideal_steering_angle"));
  ackermann_model.def("compute_outer_steering_angle",
                      &AckermannModel::ComputeOuterSteeringAngle,
                      py::arg("ideal_steering_angle"));
  ackermann_model.def("compute_steering_angles",
                      &AckermannModel::ComputeSteeringAngles,
                      py::arg("ideal_steering_angle"));
  ackermann_model.def_readonly("width", &AckermannModel::width);
  ackermann_model.def_readonly("length", &AckermannModel::length);
  ackermann_model.def_readonly("pose_size", &AckermannModel::pose_size);
  ackermann_model.def_readonly("velocity_size", &AckermannModel::velocity_size);
  ackermann_model.def_readonly("control_input_size",
                               &AckermannModel::control_input_size);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac

