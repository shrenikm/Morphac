#ifndef PLAYGROUND_STATE_H
#define PLAYGROUND_STATE_H

#include <unordered_map>

#include "constructs/include/state.h"
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
  const std::unordered_map<int, morphac::robot::blueprint::Robot&>&
  get_robot_oracle() const;
  const morphac::robot::blueprint::Robot& get_robot(const int uid) const;
  const morphac::constructs::State& get_robot_state(const int uid) const;

  void set_environment(const morphac::environments::Environment& environment);
  void set_robot_state(const morphac::constructs::State&, const int uid);

  void AddRobot(morphac::robot::blueprint::Robot& robot, const int uid);

 private:
  bool UidExistsInOracle(const int uid) const;
  morphac::environments::Environment environment_;
  std::unordered_map<int, morphac::robot::blueprint::Robot&> robot_oracle_;
};

}  // namespace simulation
}  // namespace morphac

#endif
