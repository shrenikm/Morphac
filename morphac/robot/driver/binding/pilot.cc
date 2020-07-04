#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "robot/pilot/binding/include/pilot_binding.h"

namespace morphac {
namespace robot {
namespace pilot {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_pilot, m) {
  define_pilot_binding(m);
}

}  // namespace binding
}  // namespace pilot
}  // namespace robot
}  // namespace morphac
