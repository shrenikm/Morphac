#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "constructs/include/control_input.h"

namespace morphac {
namespace constructs {
namespace binding {

void define_control_input_binding(pybind11::module& m);

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

