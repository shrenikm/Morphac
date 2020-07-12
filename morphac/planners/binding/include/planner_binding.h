#ifndef PLANNER_BINDING_H
#define PLANNER_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "planners/include/planner.h"

namespace morphac {
namespace planners {
namespace binding {

// Trampoline class as the Planner class is abstract.
class PyPlanner : public morphac::planners::Planner {};

void define_planner_binding(pybind11::module& m);

}  // namespace binding
}  // namespace planners
}  // namespace morphac

#endif
