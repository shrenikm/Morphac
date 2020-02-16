#include "mechanics/models/include/dubin_model.h"

namespace morphac {
namespace mechanics {
namespace models {

using std::cos;
using std::sin;
using std::string;

using Eigen::VectorXd;

using morphac::mechanics::models::KinematicModel;
using morphac::constructs::ControlInput;
using morphac::constructs::State;

DubinModel::DubinModel(const string name, const double speed)
    : KinematicModel(name, 3, 3, 1), speed(speed) {}

void DubinModel::ComputeStateDerivative(const State& state,
                                        const ControlInput& input,
                                        State& derivative) const {
  MORPH_REQUIRE(
      state.get_size_pose() == 3, std::invalid_argument,
      "Pose component of the state needs to be of size 3 [x, y, theta]");
  MORPH_REQUIRE(state.is_velocity_empty(), std::invalid_argument,
                "Velocity component of the state must be empty.");
  MORPH_REQUIRE(input.get_size() == 1, std::invalid_argument,
                "Control input must be of size 1.");
  MORPH_REQUIRE(
      derivative.get_size_pose() == 3, std::invalid_argument,
      "Pose component of the derivative needs to be of size 3 [x, y, theta]");
  MORPH_REQUIRE(derivative.is_velocity_empty(), std::invalid_argument,
                "Velocity component of the derivative must be empty.");
  VectorXd pose_derivative(3);
  double theta = state.get_pose_at(3);

  pose_derivative << speed * cos(theta), speed * sin(theta),
      input.get_input_at(0);
  derivative.set_pose_vector(pose_derivative);
}

State DubinModel::ComputeStateDerivative(const State& state,
                                         const ControlInput& input) const {
  MORPH_REQUIRE(
      state.get_size_pose() == 3, std::invalid_argument,
      "Pose component of the state needs to be of size 3 [x, y, theta]");
  MORPH_REQUIRE(state.is_velocity_empty(), std::invalid_argument,
                "Velocity component of the state must be empty.");
  MORPH_REQUIRE(input.get_size() == 1, std::invalid_argument,
                "Control input must be of size 1.");
  State derivative(3, 0);
  ComputeStateDerivative(state, input, derivative);
  return derivative;
}

}  // namespace models
}  // namespace mechanics
}  // namespace morphac
