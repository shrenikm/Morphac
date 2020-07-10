#include "math/numeric/include/mid_point_integrator.h"

namespace morphac {
namespace math {
namespace numeric {

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::math::numeric::Integrator;
using morphac::mechanics::models::KinematicModel;

MidPointIntegrator::MidPointIntegrator(KinematicModel& kinematic_model)
    : Integrator(kinematic_model) {}

State MidPointIntegrator::Step(const State& state,
                               const ControlInput& control_input,
                               double dt) const {
  // The two slope values.
  auto k1 = kinematic_model_.ComputeStateDerivative(state, control_input);
  auto k2 = kinematic_model_.ComputeStateDerivative(state + (dt / 2.) * k1,
                                                    control_input);

  // Normalizing the state before returning the updated state.
  return kinematic_model_.NormalizeState(state + (dt * k2));
}

}  // namespace numeric
}  // namespace math
}  // namespace morphac
