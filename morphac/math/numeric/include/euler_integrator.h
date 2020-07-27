#ifndef EULER_INTEGRATOR_H
#define EULER_INTEGRATOR_H

#include "constructs/include/control_input.h"
#include "constructs/include/state.h"
#include "math/numeric/include/integrator.h"
#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace math {
namespace numeric {

class EulerIntegrator : public morphac::math::numeric::Integrator {
 public:
  EulerIntegrator(morphac::mechanics::models::KinematicModel& kinematic_model);

  morphac::constructs::State Step(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& control_input,
      const double dt) const override;
};

}  // namespace numeric
}  // namespace math
}  // namespace morphac

#endif
