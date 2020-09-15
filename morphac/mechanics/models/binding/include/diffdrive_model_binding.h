#ifndef DIFFDRIVE_MODEL_BINDING_H
#define DIFFDRIVE_MODEL_BINDING_H

#include "mechanics/models/include/diffdrive_model.h"
#include "mechanics/models/include/kinematic_model.h"
#include "pybind11/pybind11.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

void define_diffdrive_model_binding(pybind11::module& m);

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac

#endif
