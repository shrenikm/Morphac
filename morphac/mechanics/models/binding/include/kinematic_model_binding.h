#ifndef KINEMATIC_MODEL_BINDING_H
#define KINEMATIC_MODEL_BINDING_H

#include "constructs/include/control_input.h"
#include "constructs/include/state.h"
#include "mechanics/models/include/kinematic_model.h"
#include "pybind11/pybind11.h"

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
      const morphac::constructs::ControlInput& control_input) const override {
    PYBIND11_OVERLOAD_PURE_NAME(morphac::constructs::State, KinematicModel,
                                "compute_state_derivative",
                                ComputeStateDerivative, state, control_input);
  }

  morphac::robot::blueprint::Footprint DefaultFootprint() const override {
    PYBIND11_OVERLOAD_PURE_NAME(morphac::robot::blueprint::Footprint,
                                KinematicModel, "default_footprint",
                                DefaultFootprint);
  }
};

void define_kinematic_model_binding(pybind11::module& m);

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac

#endif
