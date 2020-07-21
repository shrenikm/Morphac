#ifndef TRAJECTORY_BINDING_H
#define TRAJECTORY_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "constructs/include/trajectory.h"

namespace morphac {
namespace constructs {
namespace binding {

void define_trajectory_binding(pybind11::module& m);

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

#endif
