#include "robot/blueprint/include/robot.h"

namespace morphac {
namespace robot {
namespace blueprint {

using Eigen::MatrixXd;

using morphac::constructs::ControlInput;
using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;
using morphac::mechanics::models::KinematicModel;
using morphac::robot::blueprint::Footprint;

Robot::Robot(const KinematicModel& kinematic_model, const Footprint& footprint)
    : kinematic_model_(const_cast<KinematicModel&>(kinematic_model)),
      footprint_(footprint),
      state_(State(kinematic_model.pose_size, kinematic_model.velocity_size)) {}

Robot::Robot(const KinematicModel& kinematic_model, const Footprint& footprint,
             const State& initial_state)
    : kinematic_model_(const_cast<KinematicModel&>(kinematic_model)),
      footprint_(footprint),
      state_(initial_state) {
  MORPH_REQUIRE(
      initial_state.get_pose_size() == kinematic_model.pose_size &&
          initial_state.get_velocity_size() == kinematic_model.velocity_size,
      std::invalid_argument,
      "Kinematic model and initial state dimensions do not match.");
}

State Robot::ComputeStateDerivative(const ControlInput& control_input) const {
  MORPH_REQUIRE(
      control_input.get_size() == kinematic_model_.control_input_size,
      std::invalid_argument,
      "ControlInput dimension and kinematic model control input dimensions "
      "do not match.");
  return kinematic_model_.ComputeStateDerivative(state_, control_input);
}

State Robot::ComputeStateDerivative(const State& state,
                                    const ControlInput& control_input) const {
  // Even for a custom state, the dimensions must still match, meaning that
  // the state must correspond to the same robot.
  MORPH_REQUIRE(
      state.get_pose_size() == kinematic_model_.pose_size &&
          state.get_velocity_size() == kinematic_model_.velocity_size,
      std::invalid_argument,
      "State dimension and kinematic model state dimensions do not match.");
  MORPH_REQUIRE(
      control_input.get_size() == kinematic_model_.control_input_size,
      std::invalid_argument,
      "ControlInput dimension and kinematic model control input dimensions "
      "do not match.");
  return kinematic_model_.ComputeStateDerivative(state, control_input);
}

const KinematicModel& Robot::get_kinematic_model() const {
  return kinematic_model_;
}

const Footprint& Robot::get_footprint() const { return footprint_; }

const State& Robot::get_state() const { return state_; }

const Pose& Robot::get_pose() const { return state_.get_pose(); }

const Velocity& Robot::get_velocity() const { return state_.get_velocity(); }

void Robot::set_state(const State& state) {
  MORPH_REQUIRE(
      state_.get_pose_size() == state.get_pose_size() &&
          state_.get_velocity_size() == state.get_velocity_size(),
      std::invalid_argument,
      "Given state and robot internal state dimensions do not match.");
  state_ = state;
}

void Robot::set_pose(const Pose& pose) {
  MORPH_REQUIRE(state_.get_pose_size() == pose.get_size(),
                std::invalid_argument,
                "Given pose and robot internal pose dimensions do not match.");
  state_.set_pose(pose);
}

void Robot::set_velocity(const Velocity& velocity) {
  MORPH_REQUIRE(
      state_.get_velocity_size() == velocity.get_size(), std::invalid_argument,
      "Given velocity and robot internal velocity dimensions do not match.");
  state_.set_velocity(velocity);
}

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac
