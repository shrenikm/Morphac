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

void PlaygroundState::AddRobot(int id, const Robot& robot) {
  robot_oracle_.insert({id, robot});
}

}  // namespace simulation
}  // namespace morphac
