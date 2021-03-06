#ifndef STATE_BINDING_H
#define STATE_BINDING_H

#include "constructs/include/state.h"
#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

namespace morphac {
namespace constructs {
namespace binding {

void define_state_binding(pybind11::module& m);

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

#endif
