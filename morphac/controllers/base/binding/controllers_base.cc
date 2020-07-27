#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "controllers/base/binding/include/controller_binding.h"

namespace morphac {
namespace controllers {
namespace base {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_controllers_base_python, m) {
  define_controller_binding(m);
}

}  // namespace binding
}  // namespace base
}  // namespace controllers
}  // namespace morphac
