#ifndef MAP_CONSTANTS_BINDING_H
#define MAP_CONSTANTS_BINDING_H

#include "pybind11/pybind11.h"

#include "constants/include/map_constants.h"

namespace morphac {
namespace constants {
namespace binding {

void define_map_constants_binding(pybind11::module& m);

}  // namespace binding
}  // namespace constants
}  // namespace morphac

#endif
