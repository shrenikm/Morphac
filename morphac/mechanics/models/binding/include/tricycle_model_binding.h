#ifndef TRICYCLE_MODEL_BINDING_H
#define TRICYCLE_MODEL_BINDING_H

#include "pybind11/pybind11.h"

#include "mechanics/models/include/kinematic_model.h"
#include "mechanics/models/include/tricycle_model.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

void define_tricycle_model_binding(pybind11::module& m);

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac

#endif
