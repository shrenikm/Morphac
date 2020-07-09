#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "math/numeric/binding/include/integrator_binding.h"
#include "math/numeric/binding/include/euler_integrator_binding.h"
#include "math/numeric/binding/include/mid_point_integrator_binding.h"
#include "math/numeric/binding/include/rk4_integrator_binding.h"

namespace morphac {
namespace math {
namespace numeric {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_numeric_python, m) {
  define_integrator_binding(m);
  define_integrator_type_binding(m);
  define_euler_integrator_binding(m);
  define_mid_point_integrator_binding(m);
  define_rk4_integrator_binding(m);
}


}  // namespace binding
}  // namespace numeric
}  // namespace math
}  // namespace morphac
