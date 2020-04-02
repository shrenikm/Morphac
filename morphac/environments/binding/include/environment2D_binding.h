#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "environments/include/environment2D.h"

namespace morphac {
namespace constructs {
namespace binding {

void define_environment2D_binding(pybind11::module& m);

}  // namespace binding
}  // namespace constructs
}  // namespace morphac

