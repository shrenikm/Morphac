#include "planners/base/binding/include/planner_binding.h"

namespace morphac {
namespace planners {
namespace base {
namespace binding {

namespace py = pybind11;

using morphac::planners::base::Planner;

void define_planner_binding(py::module& m) {
  py::class_<Planner, PyPlanner> planner(m, "Planner");

  planner.def(py::init<>());
}

}  // namespace binding
}  // namespace base
}  // namespace planners
}  // namespace morphac
