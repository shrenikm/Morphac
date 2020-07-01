#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using morphac::constructs::State;

KinematicModel::KinematicModel(const int pose_size, const int velocity_size,
                               const int input_size)
    : pose_size(pose_size),
      velocity_size(velocity_size),
      input_size(input_size) {}

State KinematicModel::NormalizeState(const State& state) const {
    // Default implementation. If a KinematicModel subclass doesn't need any
    // state normalization, we return the state itself.
    return state;
}

}  // models
}  // mechanics
}  // morphac

