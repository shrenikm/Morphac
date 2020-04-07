#include "mechanics/models/include/dubin_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::cos;
using std::sin;
using std::string;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::mechanics::models::KinematicModel;
using morphac::constructs::ControlInput;
using morphac::constructs::State;

DubinModel::DubinModel(const string name, const double speed)
    : KinematicModel(name, 3, 0, 1), speed(speed) {}

State DubinModel::ComputeStateDerivative(const State& state,
                                         const ControlInput& input) const {
  MORPH_REQUIRE(
      state.get_size_pose() == 3, std::invalid_argument,
      "Pose component of the state needs to be of size 3 [x, y, theta]");
  MORPH_REQUIRE(state.IsVelocityEmpty(), std::invalid_argument,
                "Velocity component of the state must be empty.");
  MORPH_REQUIRE(input.get_size() == 1, std::invalid_argument,
                "Control input must be of size 1.");

  VectorXd pose_derivative(3);
  double theta = state.get_pose()(2);

  // Equation of the form xdot = F(x) + G(x)u
  MatrixXd F(3, 1), G(3, 1);
  F << speed * cos(theta), speed * sin(theta), 0;
  G << 0, 0, 1;

  pose_derivative = F + G * input.get_input_vector();

  State derivative = State::CreateLike(state);
  derivative.set_pose_vector(pose_derivative);

  return derivative;
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac
