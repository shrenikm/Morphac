#include "pybind11/pybind11.h"

#include "constructs/include/input.h"
#include "constructs/include/state.h"
#include "mechanics/models/include/kinematic_model.h"
#include "math/numeric/include/euler_integrator.h"
#include "math/numeric/include/integrator.h"

namespace morphac {
namespace math {
namespace numeric {
namespace binding {

void define_euler_integrator_binding(pybind11::module& m);

}  // namespace binding
}  // namespace numeric
}  // namespace math
}  // namespace morphac
