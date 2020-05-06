#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "robot/blueprint/binding/include/footprint2D_binding.h"
#include "robot/blueprint/binding/include/robot2D_binding.h"

namespace morphac {
namespace robot {
namespace blueprint {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_blueprint, m) {
  define_footprint2D_binding(m);
  define_robot2D_binding(m);
}

}  // namespace binding
}  // namespace blueprint
}  // namespace robot
}  // namespace morphac
