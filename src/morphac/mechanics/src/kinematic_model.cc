#include "mechanics/include/kinematic_model.h"

namespace morphac {
namespace mechanics {

using std::make_shared;
using std::shared_ptr;

using morphac::constructs::ControlInput;
using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;

KinematicModel::KinematicModel(const int size_pose, const int size_velocity,
                               const int size_input)
    : size_pose_(size_pose),
      size_velocity_(size_velocity),
      size_input_(size_input) {}

const int KinematicModel::get_size_pose() const { return size_pose_; }
const int KinematicModel::get_size_velocity() const { return size_velocity_; }
const int KinematicModel::get_size_input() const { return size_input_; }

}  // constructs
}  // morphac

