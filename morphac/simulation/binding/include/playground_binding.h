#ifndef PLAYGROUND_BINDING_H
#define PLAYGROUND_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "simulation/include/playground.h"

namespace morphac {
namespace simulation {
namespace binding {

void define_playground_binding(pybind11::module& m);

}  // namespace binding
}  // namespace simulation
}  // namespace morphac

#endif
