#include "pybind11/eigen.h"
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"

#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {
namespace binding {

// Trampoline class as the kinematic model class is abstract.
class PyKinematicModel : public morphac::mechanics::models::KinematicModel {
 public:
  using KinematicModel::KinematicModel;

  void ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input,
      morphac::constructs::State& derivative) const override {
    PYBIND11_OVERLOAD_PURE(void, KinematicModel, ComputeStateDerivative, state,
                           input, derivative);
  }

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input) const override {
    PYBIND11_OVERLOAD_PURE(morphac::constructs::State, KinematicModel,
                           ComputeStateDerivative, state, input);
  }
};

void define_kinematic_model_binding(pybind11::module& m);

}  // namespace binding
}  // namespace models
}  // namespace mechanics
}  // namespace morphac
