#include "constants/binding/include/environment_constants_binding.h"
#include "constants/binding/include/mechanics_constants_binding.h"
#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

namespace morphac {
namespace constants {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_constants_python, m) {
  define_environment_constants_binding(m);
  define_mechanics_constants_binding(m);
}

}  // namespace binding
}  // namespace constants
}  // namespace morphac
