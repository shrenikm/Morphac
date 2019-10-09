#include "mechanics/include/kinematic_model.h"

namespace morphac {
namespace constructs {

using std::make_shared;
using std::shared_ptr;

KinematicModel::KinematicModel(const shared_ptr<State>& state,
                               const shared_ptr<ControlInput>& input)
    : size_pose_(state->get_size_pose()), size_velocity_(state->get_size_velocity()), size_input_(input->get_size()), state_(state), input_(input) {
  derivative_ =
      make_shared<State>(state->get_pose_vector(), state->get_velocity_vector());
}

}  // constructs
}  // morphac

