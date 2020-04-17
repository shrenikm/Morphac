#ifndef DUBIN_MODEL_H
#define DUBIN_MODEL_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

#include "constructs/include/input.h"
#include "constructs/include/state.h"

#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {

class DubinModel : public morphac::mechanics::models::KinematicModel {
 public:
  DubinModel(const double speed);

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::Input& input) const override;

  const double speed;
};

}  // namespace models
}  // namespace constructs
}  // namespace morphac

#endif

