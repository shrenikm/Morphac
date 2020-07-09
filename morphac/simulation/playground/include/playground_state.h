#ifndef PLAYGROUND_STATE_H
#define PLAYGROUND_STATE_H

#include <unordered_map>

#include "constructs/include/state.h"
#include "environment/include/map.h"
#include "robot/blueprint/include/robot.h"

namespace morphac {
namespace simulation {
namespace playground {

class PlaygroundState {
 public:
  PlaygroundState(const morphac::environment::Map& map);

  // Delete copy constructor. We don't want to copy the state to avoid
  // incurring the cost of copying the map object.
  PlaygroundState(const PlaygroundState& playground_state) = delete;

  // Also deleting copy assignment.
  PlaygroundState& operator=(const PlaygroundState& playground_state) = delete;

  const morphac::environment::Map& get_map() const;
  const std::unordered_map<int, morphac::robot::blueprint::Robot&>&
  get_robot_oracle() const;
  const morphac::robot::blueprint::Robot& get_robot(const int uid) const;
  const morphac::constructs::State& get_robot_state(const int uid) const;

  void set_map(const morphac::environment::Map& map);
  void set_robot_state(const morphac::constructs::State&, const int uid);

  int NumRobots() const;
  void AddRobot(const morphac::robot::blueprint::Robot& robot, const int uid);

 private:
  bool UidExistsInRobotOracle(const int uid) const;

  morphac::environment::Map map_;
  std::unordered_map<int, morphac::robot::blueprint::Robot&> robot_oracle_;
};

}  // namespace playground
}  // namespace simulation
}  // namespace morphac

#endif
