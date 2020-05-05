#include "math/numeric/include/mid_point_integrator.h"

namespace morphac {
namespace math {
namespace numeric {

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::math::numeric::Integrator;
using morphac::mechanics::models::KinematicModel;

MidPointIntegrator::MidPointIntegrator(KinematicModel& kinematic_model)
    : Integrator(kinematic_model) {}

State MidPointIntegrator::Step(const State& state, const Input& input,
                               double dt) const {
  // State at the mid point between the current and next estimated state.
  auto mid_point_state =
      state + (dt / 2.) * kinematic_model_.ComputeStateDerivative(state, input);

  // Derivative at the mid point.
  auto mid_point_derivative =
      kinematic_model_.ComputeStateDerivative(mid_point_state, input);

  // Using the derivative mid point to compute the updated state value.
  return kinematic_model_.NormalizeState(state + (dt * mid_point_derivative));
}

}  // namespace numeric
}  // namespace math
}  // namespace morphac
