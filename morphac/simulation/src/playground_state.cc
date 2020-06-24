#include "simulation/include/playground_state.h"

namespace morphac {
namespace simulation {

using std::unordered_map;

using morphac::environments::Environment;
using morphac::robot::blueprint::Robot;

PlaygroundState::PlaygroundState(const Environment& environment)
    : environment_(environment) {}

const Environment& PlaygroundState::get_environment() const {
  return environment_;
}

const unordered_map<int, Robot>& PlaygroundState::get_robot_oracle() const {
  return robot_oracle_;
}

void PlaygroundState::set_environment(const Environment& environment) {
  environment_ = environment;
}

void PlaygroundState::AddRobot(const Robot& robot) {
  MORPH_REQUIRE(robot_oracle_.find(robot.get_uid()) == robot_oracle_.end(),
                std::logic_error,
                "Robot with this UID already exists in the state.");
  robot_oracle_.insert({robot.get_uid(), robot});
}

}  // namespace simulation
}  // namespace morphac
