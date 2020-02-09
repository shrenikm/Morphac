#include "mechanics/include/kinematic_model.h"

namespace morphac {
namespace mechanics {

using std::make_shared;
using std::shared_ptr;

using morphac::constructs::ControlInput;
using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;

KinematicModel::KinematicModel(const shared_ptr<State>& state,
                               const shared_ptr<ControlInput>& input)
    : size_pose_(state->get_size_pose()),
      size_velocity_(state->get_size_velocity()),
      size_input_(input->get_size()),
      state_(state),
      input_(input) {
  derivative_ = make_shared<State>(state->get_pose_vector(),
                                   state->get_velocity_vector());
}

const State& KinematicModel::get_derivative() const { return *derivative_; }

const State& KinematicModel::get_state() const { return *state_; }

const ControlInput& KinematicModel::get_input() const { return *input_; };

}  // constructs
}  // morphac

