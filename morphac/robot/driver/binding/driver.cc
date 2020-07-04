#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "robot/driver/binding/include/pilot_binding.h"

namespace morphac {
namespace robot {
namespace driver {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_driver, m) {
  define_pilot_binding(m);
}

}  // namespace binding
}  // namespace driver
}  // namespace robot
}  // namespace morphac
