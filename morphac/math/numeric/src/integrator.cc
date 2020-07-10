#include "math/numeric/include/integrator.h"

namespace morphac {
namespace math {
namespace numeric {

using std::min;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::KinematicModel;

Integrator::Integrator(KinematicModel& kinematic_model)
    : kinematic_model_(kinematic_model) {}

State Integrator::Integrate(const State& state,
                            const ControlInput& control_input,
                            const double time, const double dt) const {
  double elapsed_time = 0.0;
  auto updated_state = state;
  while (elapsed_time < time) {
    // In case dt isn't a factor of time, we want to make sure that the last
    // step is integrated with the correct dt (Which will be lesser than dt).
    double step_time = min(dt, time - elapsed_time);
    updated_state = Step(updated_state, control_input, step_time);
    elapsed_time += step_time;
  }

  return updated_state;
}

}  // namespace numeric
}  // namespace math
}  // namespace morphac
