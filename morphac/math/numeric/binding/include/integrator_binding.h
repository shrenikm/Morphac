#ifndef INTEGRATOR_BINDING_H
#define INTEGRATOR_BINDING_H

#include "pybind11/pybind11.h"

#include "constructs/include/input.h"
#include "constructs/include/state.h"
#include "mechanics/models/include/kinematic_model.h"
#include "math/numeric/include/integrator.h"

namespace morphac {
namespace math {
namespace numeric {
namespace binding {

// Trampoline class as the Integrator class is abstract.
class PyIntegrator : public morphac::math::numeric::Integrator {
 public:
  using Integrator::Integrator;

  morphac::constructs::State Step(const morphac::constructs::State& state,
                                  const morphac::constructs::Input& input,
                                  const double dt) const override {
    PYBIND11_OVERLOAD_PURE_NAME(morphac::constructs::State, Integrator, "step",
                                Step, state, input, dt);
  }

  morphac::constructs::State Integrate(const morphac::constructs::State& state,
                                       const morphac::constructs::Input& input,
                                       const double time,
                                       const double dt) const override {
    PYBIND11_OVERLOAD_NAME(morphac::constructs::State, Integrator, "integrate",
                           Integrate, state, input, time, dt);
  }
};

void define_integrator_binding(pybind11::module& m);

void define_integrator_type_binding(pybind11::module& m);

}  // namespace binding
}  // namespace numeric
}  // namespace math
}  // namespace morphac

#endif
