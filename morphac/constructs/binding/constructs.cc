#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "constructs/binding/include/control_input_binding.h"
#include "constructs/binding/include/coordinate2D_binding.h"
#include "constructs/binding/include/pose_binding.h"
#include "constructs/binding/include/state_binding.h"
#include "constructs/binding/include/trajectory_binding.h"
#include "constructs/binding/include/velocity_binding.h"

namespace morphac {
namespace constructs {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_constructs_python, m) {
  define_coordinate2D_binding(m);
  define_control_input_binding(m);
  define_pose_binding(m);
  define_velocity_binding(m);
  define_state_binding(m);
  define_trajectory_binding(m);
}

}  // namespace binding
}  // namespace constructs
}  // namespace morphac
