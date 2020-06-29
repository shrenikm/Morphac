#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "environment/binding/include/map_binding.h"

namespace morphac {
namespace environment {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_environment, m) { define_map_binding(m); }

}  // namespace binding
}  // namespace environment
}  // namespace morphac
