#include "constructs/include/state.h"

namespace morphac {
namespace constructs {

using std::make_unique;
using std::move;
using std::unique_ptr;

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

int State::get_size_pose() const { return pose_->get_size(); }

int State::get_size_velocity() const { return velocity_->get_size(); }

int State::get_size() const {
  return pose_->get_size() + velocity_->get_size();
}

const Pose& State::get_pose() const { return *pose_; }

const Velocity& State::get_velocity() const { return *velocity_; }

const VectorXd& State::get_pose_vector() const { return pose_->get_pose(); }

double State::get_pose_at(int index) const {
  // The Pose class getter does the argument check.
  return pose_->get_pose(index);
}

const VectorXd& State::get_velocity_vector() const {
  return velocity_->get_velocity();
}

double State::get_velocity_at(int index) const {
  // The Velocity class getter does the argument check.
  return velocity_->get_velocity(index);
}

void State::set_pose_vector(const VectorXd& pose) {
  // The Pose class setter does the argument check.
  pose_->set_pose(pose);
}

void State::set_pose_at(int index, double pose_element) {
  // The Pose class setter does the argument check.
  pose_->set_pose(index, pose_element);
}

void State::set_velocity_vector(const VectorXd& velocity) {
  // The Velocity class getter does the argument check.
  velocity_->set_velocity(velocity);
}

void State::set_velocity_at(int index, double velocity_element) {
  // The Velocity class getter does the argument check.
  velocity_->set_velocity(index, velocity_element);
}

}  // constructs
}  // morphac
