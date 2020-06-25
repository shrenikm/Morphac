#ifndef ROBOT_BINDING_H
#define ROBOT_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "constructs/include/input.h"
#include "constructs/include/state.h"
#include "robot/blueprint/include/footprint.h"
#include "robot/blueprint/include/robot.h"

namespace morphac {
namespace robot {
namespace blueprint {
namespace binding {

void define_robot_binding(pybind11::module& m);

}  // namespace binding
}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

#endif
