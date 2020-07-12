#ifndef CONTROLLER_BINDING_H
#define CONTROLLER_BINDING_H

#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "controllers/include/controller.h"

namespace morphac {
namespace controllers {
namespace binding {

// Trampoline class as the Controller class is abstract.
class PyController : public morphac::controllers::Controller {};

void define_controller_binding(pybind11::module& m);

}  // namespace binding
}  // namespace controllers
}  // namespace morphac

#endif
