#ifndef PLANNER_BINDING_H
#define PLANNER_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "planners/base/include/planner.h"

namespace morphac {
namespace planners {
namespace base {
namespace binding {

// Trampoline class as the Planner class is abstract.
class PyPlanner : public morphac::planners::base::Planner {};

void define_planner_binding(pybind11::module& m);

}  // namespace binding
}  // namespace base
}  // namespace planners
}  // namespace morphac

#endif
