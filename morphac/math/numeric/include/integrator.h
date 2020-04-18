#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace math {
namespace numeric {

class Integrator {
 public:
  Integrator(morphac::mechanics::models::KinematicModel& kinematic_model);

  virtual morphac::constructs::State Step(
      const morphac::constructs::State& state,
      const morphac::constructs::Input& input, const double dt) const = 0;

 protected:
  morphac::mechanics::models::KinematicModel& kinematic_model_;
};

}  // namespace numeric
}  // namespace math
}  // namespace morphac

#endif
