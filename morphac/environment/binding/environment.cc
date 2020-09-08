#include "environment/binding/include/map_binding.h"
#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

namespace morphac {
namespace environment {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_environment_python, m) { define_map_binding(m); }

}  // namespace binding
}  // namespace environment
}  // namespace morphac
