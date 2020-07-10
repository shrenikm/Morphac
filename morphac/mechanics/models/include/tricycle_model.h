#ifndef TRICYCLE_MODEL_H
#define TRICYCLE_MODEL_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

#include "utils/include/angle_utils.h"

#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {

class TricycleModel : public morphac::mechanics::models::KinematicModel {
 public:
  TricycleModel(const double radius, const double length);

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& control_input) const override;

  morphac::constructs::State NormalizeState(
      const morphac::constructs::State& state) const override;

  const double radius;
  const double length;
};

}  // namespace models
}  // namespace mechancis
}  // namespace morphac

#endif
