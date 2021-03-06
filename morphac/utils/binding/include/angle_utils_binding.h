#ifndef ANGLE_UTILS_BINDING_H
#define ANGLE_UTILS_BINDING_H

#include "pybind11/pybind11.h"
#include "utils/include/angle_utils.h"

namespace morphac {
namespace utils {
namespace binding {

void define_angle_utils_binding(pybind11::module& m);

}  // namespace binding
}  // namespace utils
}  // namespace morphac

#endif
