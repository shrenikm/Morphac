#include "planners/binding/include/planner_binding.h"

namespace morphac {
namespace planners {
namespace binding {

namespace py = pybind11;

using morphac::planners::Planner;

void define_planner_binding(py::module& m) {
  py::class_<Planner, PyPlanner> planner(m, "Planner");

  planner.def(py::init<>());
}

}  // binding
}  // planners
}  // morphac
