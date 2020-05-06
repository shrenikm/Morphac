#ifndef RK4_INTEGRATOR_H
#define RK4_INTEGRATOR_H

#include "math/numeric/include/integrator.h"
#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace math {
namespace numeric {

class RK4Integrator : public morphac::math::numeric::Integrator {
 public:
  RK4Integrator(morphac::mechanics::models::KinematicModel& kinematic_model);

  morphac::constructs::State Step(const morphac::constructs::State& state,
                                  const morphac::constructs::Input& input,
                                  const double dt) const override;
};

}  // namespace numeric
}  // namespace math
}  // namespace morphac

#endif
