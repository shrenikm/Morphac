#ifndef PLAYGROUND_STATE_H
#define PLAYGROUND_STATE_H

#include "environments/include/environment.h"
#include "robot/blueprint/include/robot.h"

namespace morphac {
namespace simulation {

class PlaygroundState {
 public:
  PlaygroundState(const morphac::environments::Environment& environment);

  // Delete copy constructor. We don't want to copy the state to avoid
  // incurring the cost of copying the environment object.
  PlaygroundState(const PlaygroundState& playground_state) = delete;

  // Also deleting copy assignment.
  PlaygroundState& operator=(const PlaygroundState& playground_state) = delete;

  const morphac::environments::Environment& get_environment() const;
  const std::unordered_map<int, morphac::robot::blueprint::Robot>&
  get_robot_oracle() const;

  void set_environment(const morphac::environments::Environment& environment);
  void AddRobot(int id, const morphac::robot::blueprint::Robot& robot);

 private:
  morphac::environments::Environment environment_;
  std::unordered_map<int, morphac::robot::blueprint::Robot> robot_oracle_;
};

}  // namespace simulation
}  // namespace morphac

#endif
