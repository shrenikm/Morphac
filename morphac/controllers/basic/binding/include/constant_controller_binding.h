#ifndef CONSTANT_CONTROLLER_BINDING_H
#define CONSTANT_CONTROLLER_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "controllers/basic/include/constant_controller.h"

namespace morphac {
namespace controllers {
namespace basic {
namespace binding {

void define_constant_controller_binding(pybind11::module& m);

}  // namespace binding
}  // namespace basic
}  // namespace controllers
}  // namespace morphac

#endif
