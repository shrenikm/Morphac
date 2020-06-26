#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <unordered_map>

#include "constructs/include/state.h"
#include "environments/include/environment.h"
#include "math/numeric/include/integrator.h"
#include "mechanics/models/include/kinematic_model.h"
#include "robot/blueprint/include/robot.h"
#include "robot/pilot/include/pilot.h"
#include "simulation/include/playground_state.h"
#include "utils/include/integrator_utils.h"

namespace morphac {
namespace simulation {

struct PlaygroundSpec {
  std::string name;
  double dt;

  int gui_width;
  int gui_height;
};

class Playground {
 public:
  Playground(const PlaygroundSpec& spec,
             const morphac::environments::Environment& environment);

  // Delete copy constructor.
  Playground(const Playground& playground) = delete;

  // Delete copy assignment.
  Playground& operator=(const Playground& playground) = delete;

  const PlaygroundState& get_state() const;

  const morphac::robot::blueprint::Robot& get_robot(const int uid) const;
  const morphac::constructs::State& get_robot_state(const int uid) const;
  void set_robot_state(const int uid, const morphac::constructs::State& state);

  void AddRobot(morphac::robot::blueprint::Robot& robot,
                morphac::robot::pilot::Pilot& pilot,
                const morphac::math::numeric::IntegratorType& integrator_type);

  void Execute();

 private:
  const PlaygroundSpec spec_;
  PlaygroundState playground_state_;
  std::unordered_map<int, morphac::math::numeric::Integrator&>
      integrator_oracle_;
  std::unordered_map<int, morphac::robot::pilot::Pilot&> pilot_oracle_;
};

}  // namespace simulation
}  // namespace morphac

#endif
