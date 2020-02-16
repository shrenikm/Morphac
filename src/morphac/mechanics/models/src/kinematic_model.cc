#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {

using std::make_shared;
using std::shared_ptr;
using std::string;

using morphac::constructs::ControlInput;
using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;

KinematicModel::KinematicModel(string name, int size_pose, int size_velocity,
                               int size_input)
    : name(name),
      size_pose(size_pose),
      size_velocity(size_velocity),
      size_input(size_input) {}

}  // constructs
}  // morphac

