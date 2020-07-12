#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "controllers/binding/include/controller_binding.h"

namespace morphac {
namespace controllers {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_controllers_python, m) {
  define_controller_binding(m);
}

}  // namespace binding
}  // namespace controllers
}  // namespace morphac
