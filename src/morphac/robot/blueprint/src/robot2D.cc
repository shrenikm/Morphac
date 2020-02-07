#include "robot/blueprint/include/robot2D.h"

namespace morphac {
namespace robot {
namespace blueprint {

using Eigen::MatrixXd;

using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;
using morphac::mechanics::KinematicModel;

Robot2D::Robot2D(const KinematicModel& kinematic_model, MatrixXd footprint)
    : kinematic_model_(kinematic_model), footprint_(footprint) {
  MORPH_REQUIRE(footprint.rows() > 0 && footprint.cols() > 0,
                std::invalid_argument,
                "Non-positive number of footprint coordinates.");
  MORPH_REQUIRE(footprint.cols() == 2, std::invalid_argument,
                "Footprint coordinates must be two dimensional.");
}

const KinematicModel& Robot2D::get_kinematic_model() const {
  return kinematic_model_;
}

const State& Robot2D::get_state() const { return kinematic_model_.get_state(); }

const Pose& Robot2D::get_pose() const {
  return kinematic_model_.get_state().get_pose();
}

const Velocity& Robot2D::get_velocity() const {
  return kinematic_model_.get_state().get_velocity();
}

const MatrixXd Robot2D::get_footprint() const { return footprint_; }

}  // namespace models
}  // namespace robot
}  // namespace morphac
