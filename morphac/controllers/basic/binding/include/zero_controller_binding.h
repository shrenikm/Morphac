#ifndef ZERO_CONTROLLER_BINDING_H
#define ZERO_CONTROLLER_BINDING_H

#include "controllers/basic/include/zero_controller.h"
#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

namespace morphac {
namespace controllers {
namespace basic {
namespace binding {

void define_zero_controller_binding(pybind11::module& m);

}  // namespace binding
}  // namespace basic
}  // namespace controllers
}  // namespace morphac

#endif
