#ifndef PLAYGROUND_STATE_BINDING_H
#define PLAYGROUND_STATE_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "simulation/include/playground_state.h"

namespace morphac {
namespace simulation {
namespace binding {

void define_playground_state_binding(pybind11::module& m);

}  // namespace binding
}  // namespace simulation
}  // namespace morphac

#endif
