#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "simulation/binding/include/playground_spec_binding.h"
#include "simulation/binding/include/playground_state_binding.h"

namespace morphac {
namespace simulation {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_simulation, m) {
  define_playground_spec_binding(m);
  define_playground_state_binding(m);
}

}  // namespace binding
}  // namespace simulation
}  // namespace morphac
