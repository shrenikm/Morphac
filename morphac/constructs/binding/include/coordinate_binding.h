#ifndef COORDINATE_BINDING_H
#define COORDINATE_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "constructs/include/coordinate.h"

namespace morphac {
namespace constructs {
namespace binding {

void define_coordinate_binding(pybind11::module& m);

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

#endif

