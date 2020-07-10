#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "constructs/include/control_input.h"
#include "constructs/include/state.h"
#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace math {
namespace numeric {

enum class IntegratorType {
  kEulerIntegrator,
  kMidPointIntegrator,
  kRK4Integrator
};

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

  // Function to take compute the state after a small time dt.
  virtual morphac::constructs::State Step(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& control_input,
      const double dt) const = 0;

  // Function to integrate through a larger time step. In this case, we chain
  // together individual calls to Step so that don't lose too much accuracy.
  // We asume that the given state is the initial state and the same control
  // input is applied throughout the time step.
  // A solid base implementation is provded that need not be overriden unless
  // the subclass has a better/more efficient way of handling large time step
  // integration.
  virtual morphac::constructs::State Integrate(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& control_input, const double time,
      const double dt) const;

 protected:
  morphac::mechanics::models::KinematicModel& kinematic_model_;
};

}  // namespace numeric
}  // namespace math
}  // namespace morphac

#endif
