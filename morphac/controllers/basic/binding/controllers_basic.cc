#include "controllers/basic/binding/include/constant_controller_binding.h"
#include "controllers/basic/binding/include/zero_controller_binding.h"
#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

namespace morphac {
namespace controllers {
namespace basic {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_controllers_basic_python, m) {
  define_constant_controller_binding(m);
  define_zero_controller_binding(m);
}

}  // namespace binding
}  // namespace basic
}  // namespace controllers
}  // namespace morphac
