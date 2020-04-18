#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace math {
namespace numeric {

class Integrator {
 public:
  // Integrator takes in a KinematicModel as the morphac integrator is
  // specifically designed for mobile robot integration in the simulation.
  // We assume that it is not going to be as an integrator for arbitrary
  // functions.
  // We don't use std::function as the derivative funciton would have to be
  // provided through KinematicModel (through std::bind) anyway and the python
  // binding calls might be inefficient (especially as they are called each
  // simulation step).
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
