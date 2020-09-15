#ifndef PLAYGROUND_BINDING_H
#define PLAYGROUND_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "simulation/playground/include/playground.h"

namespace morphac {
namespace simulation {
namespace playground {
namespace binding {

void define_playground_binding(pybind11::module& m);

}  // namespace binding
}  // namespace playground
}  // namespace simulation
}  // namespace morphac

#endif
