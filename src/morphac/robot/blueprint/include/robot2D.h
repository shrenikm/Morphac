#ifndef ROBOT2D_H
#define ROBOT2D_H

#include <unordered_map>

#include "Eigen/Dense"

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
          const morphac::mechanics::KinematicModel& kinematic_model,
          const morphac::robot::blueprint::Footprint2D& footprint);
  Robot2D(const std::string name,
          const morphac::mechanics::KinematicModel& kinematic_model,
          const morphac::robot::blueprint::Footprint2D& footprint,
          const morphac::constructs::State& initial_state);

  void ComputeStateDerivative(const morphac::constructs::ControlInput& input,
                              morphac::constructs::State& derivative) const;
  morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::ControlInput& input) const;

  const std::string get_name() const;
  const morphac::mechanics::KinematicModel& get_kinematic_model() const;
  const morphac::robot::blueprint::Footprint2D get_footprint() const;
  const morphac::constructs::State& get_state() const;
  const morphac::constructs::Pose& get_pose() const;
  const morphac::constructs::Velocity& get_velocity() const;

 private:
  const std::string name_;
  const morphac::mechanics::KinematicModel& kinematic_model_;
  const morphac::robot::blueprint::Footprint2D footprint_;
  const std::unique_ptr<morphac::constructs::State> state_;
};

}  // namespace models
}  // namespace robot
}  // namespace morphac

#endif
