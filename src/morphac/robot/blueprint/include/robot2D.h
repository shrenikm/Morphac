#ifndef ROBOT2D_H
#define ROBOT2D_H

#include "Eigen/Dense"

#include "constructs/include/pose.h"
#include "constructs/include/state.h"
#include "constructs/include/velocity.h"
#include "mechanics/include/kinematic_model.h"
#include "robot/blueprint/include/footprint2D.h"

namespace morphac {
namespace robot {
namespace blueprint {

class Robot2D {
 public:
  Robot2D(const morphac::mechanics::KinematicModel& kinematic_model,
          const morphac::robot::blueprint::Footprint2D& footprint);

  virtual void ComputeStateDerivative(
      const morphac::constructs::ControlInput& input,
      morphac::constructs::State& derivative) const = 0;

  virtual morphac::constructs::State ComputeStateDerivative(
      const morphac::constructs::ControlInput& input) const = 0;

  const morphac::mechanics::KinematicModel& get_kinematic_model() const;
  const morphac::constructs::State& get_state() const;
  const morphac::constructs::Pose& get_pose() const;
  const morphac::constructs::Velocity& get_velocity() const;
  const morphac::robot::blueprint::Footprint2D get_footprint() const;

 private:
  const morphac::mechanics::KinematicModel& kinematic_model_;
  const morphac::robot::blueprint::Footprint2D footprint_;
  const std::unique_ptr<morphac::constructs::State> state_;
};

}  // namespace models
}  // namespace robot
}  // namespace morphac

#endif
