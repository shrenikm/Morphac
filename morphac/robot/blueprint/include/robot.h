#ifndef ROBOT_H
#define ROBOT_H

#include "constructs/include/input.h"
#include "constructs/include/pose.h"
#include "constructs/include/state.h"
#include "constructs/include/velocity.h"

#include "mechanics/models/include/kinematic_model.h"

#include "robot/blueprint/include/footprint.h"

namespace morphac {
namespace robot {
namespace blueprint {

class Robot {
 public:
  Robot(morphac::mechanics::models::KinematicModel& kinematic_model,
        const morphac::robot::blueprint::Footprint& footprint);
  Robot(morphac::mechanics::models::KinematicModel& kinematic_model,
        const morphac::robot::blueprint::Footprint& footprint,
        const morphac::constructs::State& initial_state);

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::Input& input) const;

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::Input& input) const;

  const morphac::mechanics::models::KinematicModel& get_kinematic_model() const;
  const morphac::robot::blueprint::Footprint& get_footprint() const;
  const morphac::constructs::State& get_state() const;
  const morphac::constructs::Pose& get_pose() const;
  const morphac::constructs::Velocity& get_velocity() const;
  void set_state(const morphac::constructs::State& state);
  void set_pose(const morphac::constructs::Pose& pose);
  void set_velocity(const morphac::constructs::Velocity& velocity);

 private:
  morphac::mechanics::models::KinematicModel& kinematic_model_;
  morphac::robot::blueprint::Footprint footprint_;
  morphac::constructs::State state_;
};

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

#endif
