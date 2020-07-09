#ifndef PLAYGROUND_SPEC_BINDING_H
#define PLAYGROUND_SPEC_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "simulation/playground/include/playground_spec.h"

namespace morphac {
namespace simulation {
namespace playground {
namespace binding {

void define_playground_spec_binding(pybind11::module& m);

}  // namespace binding
}  // namespace playground
}  // namespace simulation
}  // namespace morphac

#endif
