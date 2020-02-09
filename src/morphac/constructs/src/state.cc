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

State::State(const VectorXd& pose_vector, const VectorXd& velocity_vector)
    : pose_(make_unique<Pose>(pose_vector)),
      velocity_(make_unique<Velocity>(velocity_vector)) {
  // The Pose and Velocity constructors take care of invalid arguments.
}

State::State(const Pose& pose, const Velocity& velocity)
    : pose_(make_unique<Pose>(pose)),
      velocity_(make_unique<Velocity>(velocity)) {}

State::State(unique_ptr<Pose> pose, unique_ptr<Velocity> velocity)
    : pose_(move(pose)), velocity_(move(velocity)) {}

const int State::get_size_pose() const { return pose_->get_size(); }

const int State::get_size_velocity() const { return velocity_->get_size(); }

const int State::get_size() const {
  return pose_->get_size() + velocity_->get_size();
}

const Pose& State::get_pose() const { return *pose_; }

const Velocity& State::get_velocity() const { return *velocity_; }

const VectorXd& State::get_pose_vector() const {
  return pose_->get_pose_vector();
}

double State::get_pose_at(int index) const {
  // The Pose class getter does the argument check.
  return pose_->get_pose_at(index);
}

const VectorXd& State::get_velocity_vector() const {
  return velocity_->get_velocity_vector();
}

double State::get_velocity_at(int index) const {
  // The Velocity class getter does the argument check.
  return velocity_->get_velocity_at(index);
}

const VectorXd State::get_state_vector() const {
  VectorXd state_vector(get_size());
  state_vector << get_pose_vector(), get_velocity_vector();
  return state_vector;
}

double State::get_state_at(int index) const {
  // If the index corresponds to the pose
  if (index < get_size_pose()) {
    return get_pose_at(index);
  } else {
    // Index corresponds to velocity
    return get_velocity_at(index - get_size_pose());
  }
}

void State::set_pose_vector(const VectorXd& pose_vector) {
  // The Pose class setter does the argument check.
  pose_->set_pose_vector(pose_vector);
}

void State::set_pose_at(int index, double pose_element) {
  // The Pose class setter does the argument check.
  pose_->set_pose_at(index, pose_element);
}

void State::set_velocity_vector(const VectorXd& velocity_vector) {
  // The Velocity class getter does the argument check.
  velocity_->set_velocity_vector(velocity_vector);
}

void State::set_velocity_at(int index, double velocity_element) {
  // The Velocity class getter does the argument check.
  velocity_->set_velocity_at(index, velocity_element);
}

void State::set_state_vector(const VectorXd& state_vector) {
  // Need to check if the dimensions are correct
  MORPH_REQUIRE(state_vector.size() == get_size(), std::invalid_argument,
                "State vector size is incorrect.");
  set_pose_vector(state_vector.head(get_size_pose()));
  set_velocity_vector(state_vector.tail(get_size_velocity()));
}

void State::set_state_at(int index, double state_element) {
  // The Pose and Velocity class takes care of the argument check
  if (index < get_size_pose()) {
    set_pose_at(index, state_element);
  } else {
    set_velocity_at(index - get_size_pose(), state_element);
  }
}

}  // constructs
}  // morphac
