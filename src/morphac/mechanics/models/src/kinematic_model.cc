#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::string;

using morphac::constructs::ControlInput;
using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;

KinematicModel::KinematicModel(const string name, const int size_pose,
                               const int size_velocity, const int size_input)
    : name(name),
      size_pose(size_pose),
      size_velocity(size_velocity),
      size_input(size_input) {}

State ComputeStateDerivative(const State& state,
                             const ControlInput& input) const {
}

}  // models
}  // mechanics
}  // morphac

