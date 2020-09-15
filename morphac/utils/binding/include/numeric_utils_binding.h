#ifndef NUMERIC_UTILS_BINDING_H
#define NUMERIC_UTILS_BINDING_H

#include "pybind11/pybind11.h"
#include "utils/include/numeric_utils.h"

namespace morphac {
namespace utils {
namespace binding {

void define_numeric_utils_binding(pybind11::module& m);

}  // namespace binding
}  // namespace utils
}  // namespace morphac

#endif
