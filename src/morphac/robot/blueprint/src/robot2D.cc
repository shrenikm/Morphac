#include "robot/blueprint/include/robot2D.h"

namespace morphac {
namespace robot {
namespace blueprint {

using std::make_unique;
using std::string;
using std::unordered_map;

using Eigen::MatrixXd;

using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;
using morphac::mechanics::KinematicModel;
using morphac::robot::blueprint::Footprint2D;

Robot2D::Robot2D(const Robot2DParams& params,
                 const KinematicModel& kinematic_model,
                 const Footprint2D& footprint)
    : params_(params),
      kinematic_model_(kinematic_model),
      footprint_(footprint),
      state_(make_unique<State>(kinematic_model.get_size_pose(),
                                kinematic_model.get_size_velocity())) {}

const Robot2DParams& Robot2D::get_params() const { return params_; }

const KinematicModel& Robot2D::get_kinematic_model() const {
  return kinematic_model_;
}

const Footprint2D Robot2D::get_footprint() const { return footprint_; }

const State& Robot2D::get_state() const { return *state_.get(); }

const Pose& Robot2D::get_pose() const { return state_->get_pose(); }

const Velocity& Robot2D::get_velocity() const { return state_->get_velocity(); }

}  // namespace models
}  // namespace robot
}  // namespace morphac
