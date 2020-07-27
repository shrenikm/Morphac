#ifndef ENVIRONMENT_BINDING_H
#define ENVIRONMENT_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "environment/include/map.h"

namespace morphac {
namespace environment {
namespace binding {

void define_map_binding(pybind11::module& m);

}  // namespace binding
}  // namespace environment
}  // namespace morphac

#endif
