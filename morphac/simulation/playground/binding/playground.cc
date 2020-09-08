#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"
#include "simulation/playground/binding/include/playground_binding.h"
#include "simulation/playground/binding/include/playground_spec_binding.h"
#include "simulation/playground/binding/include/playground_state_binding.h"

namespace morphac {
namespace simulation {
namespace playground {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_playground_python, m) {
  define_playground_spec_binding(m);
  define_playground_state_binding(m);
  define_playground_binding(m);
}

}  // namespace binding
}  // namespace playground
}  // namespace simulation
}  // namespace morphac
