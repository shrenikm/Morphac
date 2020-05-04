#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using morphac::constructs::State;

KinematicModel::KinematicModel(const int size_pose, const int size_velocity,
                               const int size_input)
    : size_pose(size_pose),
      size_velocity(size_velocity),
      size_input(size_input) {}

State KinematicModel::NormalizeState(const State& state) const {
    // Default implementation. If a KinematicModel subclass doesn't need any
    // state normalization, we return the state itself.
    return state;
}

}  // models
}  // mechanics
}  // morphac

