#ifndef RK4_INTEGRATOR_BINDING_H
#define RK4_INTEGRATOR_BINDING_H

#include "constructs/include/control_input.h"
#include "constructs/include/state.h"
#include "math/numeric/include/integrator.h"
#include "math/numeric/include/rk4_integrator.h"
#include "mechanics/models/include/kinematic_model.h"
#include "pybind11/pybind11.h"

namespace morphac {
namespace math {
namespace numeric {
namespace binding {

void define_rk4_integrator_binding(pybind11::module& m);

}  // namespace binding
}  // namespace numeric
}  // namespace math
}  // namespace morphac

#endif
