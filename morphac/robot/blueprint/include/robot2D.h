#ifndef ROBOT2D_H
#define ROBOT2D_H

#include <unordered_map>

#include "Eigen/Dense"

#include "constructs/include/control_input.h"
#include "constructs/include/pose.h"
#include "constructs/include/state.h"
#include "constructs/include/velocity.h"
#include "mechanics/models/include/kinematic_model.h"
#include "robot/blueprint/include/footprint2D.h"

namespace morphac {
namespace robot {
namespace blueprint {

class Robot2D {
 public:
  Robot2D(const std::string name,
          morphac::mechanics::models::KinematicModel& kinematic_model,
          const morphac::robot::blueprint::Footprint2D& footprint);
  Robot2D(const std::string name,
          morphac::mechanics::models::KinematicModel& kinematic_model,
          const morphac::robot::blueprint::Footprint2D& footprint,
          const morphac::constructs::State& initial_state);

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::ControlInput& input) const;

  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::State& state,
      const morphac::constructs::ControlInput& input) const;

  std::string get_name() const;
  const morphac::mechanics::models::KinematicModel& get_kinematic_model() const;
  const morphac::robot::blueprint::Footprint2D& get_footprint() const;
  const morphac::constructs::State& get_state() const;
  const morphac::constructs::Pose& get_pose() const;
  const morphac::constructs::Velocity& get_velocity() const;

 private:
  std::string name_;
  morphac::mechanics::models::KinematicModel& kinematic_model_;
  morphac::robot::blueprint::Footprint2D footprint_;
  morphac::constructs::State state_;
};

}  // namespace blueprint
}  // namespace robot
}  // namespace morphac

#endif
