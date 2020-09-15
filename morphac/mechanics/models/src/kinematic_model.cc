#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using morphac::constructs::State;

KinematicModel::KinematicModel(const int pose_size, const int velocity_size,
                               const int control_input_size)
    : pose_size(pose_size),
      velocity_size(velocity_size),
      control_input_size(control_input_size) {}

State KinematicModel::NormalizeState(const State& state) const {
  // Default implementation. If a KinematicModel subclass doesn't need any
  // state normalization, we return the state itself.
  return state;
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac
