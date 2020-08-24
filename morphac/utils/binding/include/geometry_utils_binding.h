#ifndef GEOMETRY_UTILS_BINDING_H
#define GEOMETRY_UTILS_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "utils/include/geometry_utils.h"

namespace morphac {
namespace utils {
namespace binding {

void define_geometry_utils_binding(pybind11::module& m);

}  // namespace binding
}  // namespace utils
}  // namespace morphac

#endif
