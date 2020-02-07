#ifndef ROBOT2D_H
#define ROBOT2D_H

#include "Eigen/Dense"

#include "constructs/include/pose.h"
#include "constructs/include/state.h"
#include "constructs/include/velocity.h"
#include "mechanics/include/kinematic_model.h"

namespace morphac {
namespace robot {
namespace blueprint {

class Robot2D {
  public:
    Robot2D(const morphac::mechanics::KinematicModel& kinematic_model, Eigen::MatrixXd footprint);
    const morphac::mechanics::KinematicModel& get_kinematic_model() const;
    const morphac::constructs::State& get_state() const;
    const morphac::constructs::Pose& get_pose() const;
    const morphac::constructs::Velocity& get_velocity() const;
    const Eigen::MatrixXd get_footprint() const;

  private:
    const morphac::mechanics::KinematicModel& kinematic_model_;
    const Eigen::MatrixXd footprint_;
};


} // namespace models
} // namespace robot
} // namespace morphac

#endif
