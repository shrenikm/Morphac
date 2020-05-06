#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "environments/binding/include/environment2D_binding.h"

namespace morphac {
namespace environments {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_environments, m) {
  define_environment2D_binding(m);
}

}  // namespace binding
}  // namespace environments
}  // namespace morphac
