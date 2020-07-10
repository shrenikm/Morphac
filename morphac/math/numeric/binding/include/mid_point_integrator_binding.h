#ifndef MID_POINT_INTEGRATOR_BINDING_H
#define MID_POINT_INTEGRATOR_BINDING_H

#include "pybind11/pybind11.h"

#include "constructs/include/control_input.h"
#include "constructs/include/state.h"
#include "math/numeric/include/integrator.h"
#include "math/numeric/include/mid_point_integrator.h"
#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace math {
namespace numeric {
namespace binding {

void define_mid_point_integrator_binding(pybind11::module& m);

}  // namespace binding
}  // namespace numeric
}  // namespace math
}  // namespace morphac

#endif
