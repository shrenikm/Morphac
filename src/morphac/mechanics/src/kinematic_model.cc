#include "mechanics/include/kinematic_model.h"

namespace morphac {
namespace mechanics {

using std::make_shared;
using std::shared_ptr;

using morphac::constructs::ControlInput;
using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;

KinematicModel::KinematicModel(int size_pose, int size_velocity, int size_input)
    : size_pose_(size_pose),
      size_velocity_(size_velocity),
      size_input_(size_input) {}

}  // constructs
}  // morphac

