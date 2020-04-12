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
      "Kinematic model and initial state dimensions mismatch.");
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

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac
