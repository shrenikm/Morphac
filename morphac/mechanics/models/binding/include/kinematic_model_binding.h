#ifndef KINEMATIC_MODEL_BINDING_H
#define KINEMATIC_MODEL_BINDING_H

#include "pybind11/pybind11.h"

#include "constructs/include/input.h"
#include "constructs/include/state.h"
#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

// Trampoline class as the KinematicModel class is abstract.
class PyKinematicModel : public morphac::mechanics::models::KinematicModel {
 public:
  using KinematicModel::KinematicModel;

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::Input& input) const override {
    PYBIND11_OVERLOAD_PURE_NAME(morphac::constructs::State, KinematicModel,
                                "compute_state_derivative",
                                ComputeStateDerivative, state, input);
  }
};

void define_kinematic_model_binding(pybind11::module& m);

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac

#endif
