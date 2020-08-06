#ifndef DUBIN_MODEL_H
#define DUBIN_MODEL_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"
#include "mechanics/models/include/kinematic_model.h"
#include "utils/include/angle_utils.h"

namespace morphac {
namespace mechanics {
namespace models {

class DubinModel : public morphac::mechanics::models::KinematicModel {
 public:
  DubinModel(const double speed);

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& control_input) const override;

  morphac::constructs::State NormalizeState(
      const morphac::constructs::State& state) const override;

  const double speed;
};

}  // namespace models
}  // namespace constructs
}  // namespace morphac

#endif

