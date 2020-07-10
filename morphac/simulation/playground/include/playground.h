#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <unordered_map>

#include "constructs/include/state.h"
#include "environment/include/map.h"
#include "math/numeric/include/euler_integrator.h"
#include "math/numeric/include/integrator.h"
#include "mechanics/models/include/kinematic_model.h"
#include "robot/blueprint/include/robot.h"
#include "robot/pilot/include/pilot.h"
#include "simulation/playground/include/playground_spec.h"
#include "simulation/playground/include/playground_state.h"
#include "utils/include/integrator_utils.h"

namespace morphac {
namespace simulation {
namespace playground {

class Playground {
 public:
  Playground(const PlaygroundSpec& spec, const morphac::environment::Map& map);

  // Delete copy constructor.
  Playground(const Playground& playground) = delete;

  // Delete copy assignment.
  Playground& operator=(const Playground& playground) = delete;

  PlaygroundState& get_state();

  const std::unordered_map<int, morphac::robot::pilot::Pilot&>&
  get_pilot_oracle() const;
  const morphac::robot::pilot::Pilot& get_pilot(const int uid) const;
  const morphac::math::numeric::Integrator& get_integrator(const int uid) const;

  void AddRobot(const morphac::robot::blueprint::Robot& robot,
                const morphac::robot::pilot::Pilot& pilot,
                const morphac::math::numeric::IntegratorType& integrator_type,
                const int uid);

  void Execute();

 private:
  bool UidExistsInIntegratorOracle(const int uid) const;
  bool UidExistsInPilotOracle(const int uid) const;

  const PlaygroundSpec spec_;
  PlaygroundState playground_state_;
  std::unordered_map<int, morphac::robot::pilot::Pilot&> pilot_oracle_;
  std::unordered_map<int, std::unique_ptr<morphac::math::numeric::Integrator>>
      integrator_oracle_;
};

}  // namespace playground
}  // namespace simulation
}  // namespace morphac

#endif
