#include "mechanics/models/include/dubin_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::cos;
using std::sin;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::constants::DubinModelConstants;
using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::math::geometry::TriangleShape;
using morphac::mechanics::models::KinematicModel;
using morphac::robot::blueprint::Footprint;
using morphac::utils::NormalizeAngle;

DubinModel::DubinModel(const double speed)
    : KinematicModel(3, 0, 1), speed(speed) {}

State DubinModel::ComputeStateDerivative(
    const State& state, const ControlInput& control_input) const {
  MORPH_REQUIRE(
      state.get_pose_size() == 3, std::invalid_argument,
      "Pose component of the state needs to be of size 3 [x, y, theta]");
  MORPH_REQUIRE(state.IsVelocityEmpty(), std::invalid_argument,
                "Velocity component of the state must be empty.");
  MORPH_REQUIRE(control_input.get_size() == 1, std::invalid_argument,
                "ControlInput must be of size 1.");

  VectorXd pose_derivative(3);
  double theta = state[2];

  // Equation of the form xdot = F(x) + G(x)u
  MatrixXd F(3, 1), G(3, 1);
  F << speed * cos(theta), speed * sin(theta), 0;
  G << 0, 0, 1;

  pose_derivative = F + G * control_input.get_data();

  // Return the derivative.
  return State(pose_derivative, VectorXd::Zero(0));
}

State DubinModel::NormalizeState(const State& state) const {
  // For the dubin model, we normalize the pose angle.
  State normalized_state = state;
  normalized_state[2] = NormalizeAngle(normalized_state[2]);

  return normalized_state;
}

Footprint DubinModel::DefaultFootprint() const {
  // Default triangular footprint.
  return Footprint::CreateTriangularFootprint(
      TriangleShape{DubinModelConstants::DEFAULT_BASE,
                    DubinModelConstants::DEFAULT_HEIGHT, -M_PI / 2.});
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac
