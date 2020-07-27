#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "planners/base/binding/include/planner_binding.h"

namespace morphac {
namespace planners {
namespace base {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_planners_python, m) {
  define_planner_binding(m);
}

}  // namespace binding
}  // namespace base
}  // namespace planners
}  // namespace morphac
