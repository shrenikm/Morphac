#include "simulation/include/playground.h"

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

Playground::Playground(const PlaygroundSpec& spec,
                       const Environment& environment)
    : spec_(spec), playground_state_(environment) {}

const PlaygroundState& Playground::get_state() const {
    return playground_state_;
}

}  // namespace simulation
}  // namespace morphac
