#include "math/numeric/include/euler_integrator.h"

namespace morphac {
namespace math {
namespace numeric {

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::math::numeric::Integrator;
using morphac::mechanics::models::KinematicModel;

EulerIntegrator::EulerIntegrator(KinematicModel& kinematic_model)
    : Integrator(kinematic_model) {}

State EulerIntegrator::Step(const State& state,
                            const ControlInput& control_input,
                            double dt) const {
  auto derivative =
      kinematic_model_.ComputeStateDerivative(state, control_input);

  // Integrate, normalize and return. We normalize to make sure that the output
  // state is good to use in simulations, etc directly.
  return kinematic_model_.NormalizeState(state + (dt * derivative));
}

}  // namespace numeric
}  // namespace math
}  // namespace morphac
