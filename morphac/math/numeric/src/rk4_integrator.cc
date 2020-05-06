#include "math/numeric/include/rk4_integrator.h"

namespace morphac {
namespace math {
namespace numeric {

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::math::numeric::Integrator;
using morphac::mechanics::models::KinematicModel;

RK4Integrator::RK4Integrator(KinematicModel& kinematic_model)
    : Integrator(kinematic_model) {}

State RK4Integrator::Step(const State& state, const Input& input,
                          double dt) const {
  // The four slope values.
  auto k1 = kinematic_model_.ComputeStateDerivative(state, input);
  auto k2 =
      kinematic_model_.ComputeStateDerivative(state + (dt / 2.) * k1, input);
  auto k3 =
      kinematic_model_.ComputeStateDerivative(state + (dt / 2.) * k2, input);
  auto k4 = kinematic_model_.ComputeStateDerivative(state + dt * k3, input);

  // Normalizing the state before returning the updated state.
  return kinematic_model_.NormalizeState(
      state + ((1. / 6.) * dt * (k1 + 2 * k2 + 2 * k3 + k4)));
}

}  // namespace numeric
}  // namespace math
}  // namespace morphac
