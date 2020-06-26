#include "simulation/include/playground_state.h"

namespace morphac {
namespace simulation {

using std::unordered_map;

using morphac::constructs::State;
using morphac::environments::Environment;
using morphac::robot::blueprint::Robot;

PlaygroundState::PlaygroundState(const Environment& environment)
    : environment_(environment) {}

const Environment& PlaygroundState::get_environment() const {
  return environment_;
}

const unordered_map<int, Robot&>& PlaygroundState::get_robot_oracle() const {
  return robot_oracle_;
}

const State& PlaygroundState::get_robot_state(const int uid) const {
  // Make sure that a robot with the given uid exists in the oracle.
  MORPH_REQUIRE(robot_oracle_.find(uid) == robot_oracle_.end(),
                std::logic_error,
                "Robot with this UID already exists in the state.");
  // We can't use the [] operator as the values are references.
  return robot_oracle_.find(uid)->second.get_state();
}

void PlaygroundState::set_environment(const Environment& environment) {
  environment_ = environment;
}

// void PlaygroundState::set_robot_state(const int uid, const State& state) {
//  // Make sure that a robot with the given uid exists in the oracle.
//  MORPH_REQUIRE(robot_oracle_.find(uid) != robot_oracle_.end(),
//                std::invalid_argument,
//                "Robot with the given UID does not exist.");
//  robot_oracle_[uid].set_state(state);
//}

//void PlaygroundState::AddRobot(const Robot& robot) {
//  MORPH_REQUIRE(robot_oracle_.find(robot.get_uid()) == robot_oracle_.end(),
//                std::logic_error,
//                "Robot with this UID already exists in the state.");
//  robot_oracle_.insert({robot.get_uid(), robot});
//}

}  // namespace simulation
}  // namespace morphac
