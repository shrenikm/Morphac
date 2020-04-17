#include "math/numeric/include/euler_integrator.h"

namespace morphac {
namespace math {
namespace numeric {

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::math::numeric::Integrator;
using morphac::mechanics::models::KinematicModel;

EulerIntegrator::EulerIntegrator(KinematicModel& kinematic_model)
    : Integrator(kinematic_model) {}

State EulerIntegrator::Step(const State& state, const Input& input, double dt) {
  auto derivative = kinematic_model_.ComputeStateDerivative(state, input);

  return state + (dt * derivative);
}

}  // namespace numeric
}  // namespace math
}  // namespace morphac
