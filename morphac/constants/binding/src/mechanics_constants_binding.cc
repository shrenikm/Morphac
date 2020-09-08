#include "constants/binding/include/mechanics_constants_binding.h"

namespace morphac {
namespace constants {
namespace binding {

namespace py = pybind11;

using morphac::constants::AckermannModelConstants;
using morphac::constants::DiffdriveModelConstants;
using morphac::constants::DubinModelConstants;
using morphac::constants::TricycleModelConstants;

void define_mechanics_constants_binding(py::module& m) {
  py::class_<AckermannModelConstants> ackermann_model_constants(
      m, "AckermannModelConstants");
  ackermann_model_constants.def_readonly_static(
      "DEFAULT_WHEEL_DIAMETER_SCALER",
      &AckermannModelConstants::DEFAULT_WHEEL_DIAMETER_SCALER);
  ackermann_model_constants.def_readonly_static(
      "DEFAULT_WHEEL_SIZE_RATIO",
      &AckermannModelConstants::DEFAULT_WHEEL_SIZE_RATIO);
  ackermann_model_constants.def_readonly_static(
      "DEFAULT_WIDTH_BUFFER_SCALER",
      &AckermannModelConstants::DEFAULT_WIDTH_BUFFER_SCALER);
  ackermann_model_constants.def_readonly_static(
      "DEFAULT_WIDTH_BUFFER", &AckermannModelConstants::DEFAULT_WIDTH_BUFFER);
  ackermann_model_constants.def_readonly_static(
      "DEFAULT_LENGTH_BUFFER_SCALER",
      &AckermannModelConstants::DEFAULT_LENGTH_BUFFER_SCALER);
  ackermann_model_constants.def_readonly_static(
      "DEFAULT_LENGTH_BUFFER", &AckermannModelConstants::DEFAULT_LENGTH_BUFFER);

  py::class_<DiffdriveModelConstants> diffdrive_model_constants(
      m, "DiffdriveModelConstants");
  diffdrive_model_constants.def_readonly_static(
      "DEFAULT_WHEEL_SIZE_RATIO",
      &DiffdriveModelConstants::DEFAULT_WHEEL_SIZE_RATIO);
  diffdrive_model_constants.def_readonly_static(
      "DEFAULT_WIDTH_BUFFER_SCALER",
      &DiffdriveModelConstants::DEFAULT_WIDTH_BUFFER_SCALER);
  diffdrive_model_constants.def_readonly_static(
      "DEFAULT_WIDTH_BUFFER", &DiffdriveModelConstants::DEFAULT_WIDTH_BUFFER);

  py::class_<DubinModelConstants> dubin_model_constants(m,
                                                        "DubinModelConstants");
  dubin_model_constants.def_readonly_static("DEFAULT_BASE",
                                            &DubinModelConstants::DEFAULT_BASE);
  dubin_model_constants.def_readonly_static(
      "DEFAULT_HEIGHT", &DubinModelConstants::DEFAULT_HEIGHT);

  py::class_<TricycleModelConstants> tricycle_model_constants(
      m, "TricycleModelConstants");
  tricycle_model_constants.def_readonly_static(
      "DEFAULT_FRONT_WHEEL_DIAMETER_SCALER",
      &TricycleModelConstants::DEFAULT_FRONT_WHEEL_DIAMETER_SCALER);
  tricycle_model_constants.def_readonly_static(
      "DEFAULT_FRONT_WHEEL_SIZE_RATIO",
      &TricycleModelConstants::DEFAULT_FRONT_WHEEL_SIZE_RATIO);
  tricycle_model_constants.def_readonly_static(
      "DEFAULT_BACK_WHEEL_DIAMETER_SCALER",
      &TricycleModelConstants::DEFAULT_BACK_WHEEL_DIAMETER_SCALER);
  tricycle_model_constants.def_readonly_static(
      "DEFAULT_BACK_WHEEL_SIZE_RATIO",
      &TricycleModelConstants::DEFAULT_BACK_WHEEL_SIZE_RATIO);
  tricycle_model_constants.def_readonly_static(
      "DEFAULT_WIDTH_BUFFER_SCALER",
      &TricycleModelConstants::DEFAULT_WIDTH_BUFFER_SCALER);
  tricycle_model_constants.def_readonly_static(
      "DEFAULT_WIDTH_BUFFER", &TricycleModelConstants::DEFAULT_WIDTH_BUFFER);
  tricycle_model_constants.def_readonly_static(
      "DEFAULT_LENGTH_BUFFER_SCALER",
      &TricycleModelConstants::DEFAULT_LENGTH_BUFFER_SCALER);
  tricycle_model_constants.def_readonly_static(
      "DEFAULT_LENGTH_BUFFER", &TricycleModelConstants::DEFAULT_LENGTH_BUFFER);
}

}  // namespace binding
}  // namespace constants
}  // namespace morphac