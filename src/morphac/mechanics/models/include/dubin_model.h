#ifndef DUBIN_MODEL_H
#define DUBIN_MODEL_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"
#include "constructs/include/control_input.h"
#include "constructs/include/state.h"
#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {

class DubinModel : public morphac::mechanics::models::KinematicModel {
 public:
  DubinModel(const std::string name, const double speed);

  void ComputeStateDerivative(const morphac::constructs::State& state,
                              const morphac::constructs::ControlInput& input,
                              morphac::constructs::State& derivative) const;
  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input) const;

  const double speed;
};

}  // namespace models
}  // namespace constructs
}  // namespace morphac

#endif

