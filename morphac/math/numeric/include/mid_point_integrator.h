#ifndef MID_POINT_INTEGRATOR_H
#define MID_POINT_INTEGRATOR_H

#include "math/numeric/include/integrator.h"
#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace math {
namespace numeric {

class MidPointIntegrator : public morphac::math::numeric::Integrator {
 public:
  MidPointIntegrator(
      morphac::mechanics::models::KinematicModel& kinematic_model);

  morphac::constructs::State Step(const morphac::constructs::State& state,
                                  const morphac::constructs::Input& input,
                                  const double dt) const override;
};

}  // namespace numeric
}  // namespace math
}  // namespace morphac

#endif
