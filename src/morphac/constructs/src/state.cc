#include "constructs/include/state.h"

namespace morphac {
namespace constructs {

using std::make_unique;
using std::unique_ptr;
using std::move;

using Eigen::VectorXd;

using morphac::constructs::Pose;
using morphac::constructs::Velocity;

State::State(int size_pose, int size_velocity)
    : pose_(make_unique<Pose>(size_pose)),
      velocity_(make_unique<Velocity>(size_velocity)) {
  // The Pose and Velocity constructors take care of invalid arguments.
}

State::State(VectorXd pose, VectorXd velocity)
    : pose_(make_unique<Pose>(pose)),
      velocity_(make_unique<Velocity>(velocity)) {
  // The Pose and Velocity constructors take care of invalid arguments.
}

State::State(unique_ptr<Pose> pose, unique_ptr<Velocity> velocity)
    : pose_(move(pose)), velocity_(move(velocity)) {}

int State::get_size_pose() { return pose_->get_size(); }

int State::get_size_velocity() { return velocity_->get_size(); }

const Pose& State::get_pose() { return *pose_; }

const Velocity& State::get_velocity() { return *velocity_; }

}  // constructs
}  // morphac
