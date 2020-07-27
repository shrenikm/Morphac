#ifndef CONTROLLER_BINDING_H
#define CONTROLLER_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "controllers/base/include/controller.h"

namespace morphac {
namespace controllers {
namespace base {
namespace binding {

// Trampoline class as the Controller class is abstract.
class PyController : public morphac::controllers::base::Controller {};

void define_controller_binding(pybind11::module& m);

}  // namespace binding
}  // namespace base
}  // namespace controllers
}  // namespace morphac

#endif
