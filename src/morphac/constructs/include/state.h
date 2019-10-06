#ifndef STATE_H
#define STATE_H

#include <memory>

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"
#include "constructs/include/pose.h"
#include "constructs/include/velocity.h"

namespace morphac {
namespace constructs {

class State {
 public:
  State(int size_pose, int size_velocity);
  State(Eigen::VectorXd pose, Eigen::VectorXd velocity);
  State(std::unique_ptr<morphac::constructs::Pose> pose,
        std::unique_ptr<morphac::constructs::Velocity> velocity);
  State(const State& state) = delete;

  int get_size_pose();
  int get_size_velocity();
  const morphac::constructs::Pose& get_pose();
  const morphac::constructs::Velocity& get_velocity();

 private:
  std::unique_ptr<morphac::constructs::Pose> pose_;
  std::unique_ptr<morphac::constructs::Velocity> velocity_;
};

}  // namespace constructs
}  // namespace morphac

#endif
