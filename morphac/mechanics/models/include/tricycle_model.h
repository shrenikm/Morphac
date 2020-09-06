#ifndef TRICYCLE_MODEL_H
#define TRICYCLE_MODEL_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"
#include "mechanics/models/include/kinematic_model.h"
#include "utils/include/angle_utils.h"

namespace morphac {
namespace mechanics {
namespace models {

class TricycleModel : public morphac::mechanics::models::KinematicModel {
 public:
  TricycleModel(const double width, const double length);

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& control_input) const override;

  morphac::constructs::State NormalizeState(
      const morphac::constructs::State& state) const override;

  const double width;
  const double length;
};

}  // namespace models
}  // namespace mechancis
}  // namespace morphac

#endif
