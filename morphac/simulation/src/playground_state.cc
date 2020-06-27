#include "simulation/include/playground_state.h"

namespace morphac {
namespace simulation {

using std::unordered_map;

using morphac::constructs::State;
using morphac::environments::Environment;
using morphac::robot::blueprint::Robot;

PlaygroundState::PlaygroundState(const Environment& environment)
    : environment_(environment) {}

bool PlaygroundState::UidExistsInOracle(const int uid) const {
  if (robot_oracle_.find(uid) == robot_oracle_.end()) {
    // Given uid doesn't exist in the robot oracle.
    return false;
  }
  return true;
}

const Environment& PlaygroundState::get_environment() const {
  return environment_;
}

const unordered_map<int, Robot&>& PlaygroundState::get_robot_oracle() const {
  return robot_oracle_;
}

const State& PlaygroundState::get_robot_state(const int uid) const {
  // Make sure that a robot with the given uid exists in the oracle.
  MORPH_REQUIRE(
      UidExistsInOracle(uid), std::logic_error,
      "Robot with the given UID does not exist in the playground state.");
  // We can't use the [] operator as the values are references.
  return robot_oracle_.find(uid)->second.get_state();
}

void PlaygroundState::set_environment(const Environment& environment) {
  environment_ = environment;
}

void PlaygroundState::set_robot_state(const State& state, const int uid) {
  // Make sure that a robot with the given uid exists in the oracle.
  MORPH_REQUIRE(
      UidExistsInOracle(uid), std::invalid_argument,
      "Robot with the given UID does not exist in the playground state.");
  robot_oracle_.find(uid)->second.set_state(state);
}

void PlaygroundState::AddRobot(Robot& robot, const int uid) {
  MORPH_REQUIRE(!UidExistsInOracle(uid), std::logic_error,
                "Robot with this UID already exists in the state.");
  robot_oracle_.insert({uid, robot});
}

}  // namespace simulation
}  // namespace morphac
