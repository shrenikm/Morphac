#include "pybind11/pybind11.h"

#include "mechanics/models/binding/include/kinematic_model_binding.h"
#include "mechanics/models/binding/include/ackermann_model_binding.h"
#include "mechanics/models/binding/include/diffdrive_model_binding.h"
#include "mechanics/models/binding/include/dubin_model_binding.h"
#include "mechanics/models/binding/include/tricycle_model_binding.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

PYBIND11_MODULE(_binding_models_python, m) {
  define_kinematic_model_binding(m);
  define_ackermann_model_binding(m);
  define_diffdrive_model_binding(m);
  define_dubin_model_binding(m);
  define_tricycle_model_binding(m);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
