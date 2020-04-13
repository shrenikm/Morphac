#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "mechanics/models/binding/include/diffdrive_model_binding.h"
// include "mechanics/models/binding/include/dubin_model_binding.h"
#include "mechanics/models/binding/include/kinematic_model_binding.h"
// include "mechanics/models/binding/include/tricycle_model_binding.h"

#include "mechanics/models/include/diffdrive_model.h"
#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

namespace py = pybind11;

using std::string;
using morphac::mechanics::models::KinematicModel;
using morphac::mechanics::models::DiffDriveModel;

PYBIND11_MODULE(_binding_models, m) {
  define_kinematic_model_binding(m);
  define_diffdrive_model_binding(m);
}

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac