#include "robot/blueprint/include/robot2D.h"

namespace morphac {
namespace robot {
namespace blueprint {

using std::make_unique;
using std::string;
using std::unordered_map;

using Eigen::MatrixXd;

using morphac::constructs::Input;
using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;
using morphac::mechanics::models::KinematicModel;
using morphac::robot::blueprint::Footprint2D;

Robot2D::Robot2D(const string name, KinematicModel& kinematic_model,
                 const Footprint2D& footprint)
    : name_(name),
      kinematic_model_(kinematic_model),
      footprint_(footprint),
      state_(State(kinematic_model.size_pose, kinematic_model.size_velocity)) {}

Robot2D::Robot2D(const string name, KinematicModel& kinematic_model,
                 const Footprint2D& footprint, const State& initial_state)
    : name_(name),
      kinematic_model_(kinematic_model),
      footprint_(footprint),
      state_(initial_state) {
  MORPH_REQUIRE(
      initial_state.get_size_pose() == kinematic_model.size_pose &&
          initial_state.get_size_velocity() == kinematic_model.size_velocity,
      std::invalid_argument,
      "Kinematic model and initial state dimensions do not match.");
}

State Robot2D::ComputeStateDerivative(const Input& input) const {
  return kinematic_model_.ComputeStateDerivative(state_, input);
}

State Robot2D::ComputeStateDerivative(const State& state,
                                      const Input& input) const {
  return kinematic_model_.ComputeStateDerivative(state, input);
}

string Robot2D::get_name() const { return name_; }

const KinematicModel& Robot2D::get_kinematic_model() const {
  return kinematic_model_;
}

const Footprint2D& Robot2D::get_footprint() const { return footprint_; }

const State& Robot2D::get_state() const { return state_; }

const Pose& Robot2D::get_pose() const { return state_.get_pose(); }

const Velocity& Robot2D::get_velocity() const { return state_.get_velocity(); }

void Robot2D::set_state(const State& state) {
  MORPH_REQUIRE(
      state_.get_size_pose() == state.get_size_pose() &&
          state_.get_size_velocity() == state.get_size_velocity(),
      std::invalid_argument,
      "Given state and robot internal state dimensions do not match.");
  state_ = state;
}

void Robot2D::set_pose(const Pose& pose) {
  MORPH_REQUIRE(state_.get_size_pose() == pose.get_size(),
                std::invalid_argument,
                "Given pose and robot internal pose dimensions do not match.");
  state_.set_pose(pose);
}

void Robot2D::set_velocity(const Velocity& velocity) {
  MORPH_REQUIRE(
      state_.get_size_velocity() == velocity.get_size(), std::invalid_argument,
      "Given velocity and robot internal velocity dimensions do not match.");
  state_.set_velocity(velocity);
}

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac
