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

  int get_size_pose() const;
  int get_size_velocity() const;
  int get_size() const;
  const morphac::constructs::Pose& get_pose() const;
  const morphac::constructs::Velocity& get_velocity() const;
  const Eigen::VectorXd& get_pose_vector() const;
  double get_pose_at(int index) const;
  const Eigen::VectorXd& get_velocity_vector() const;
  double get_velocity_at(int index) const;
  void set_pose_vector(const Eigen::VectorXd& pose);
  void set_pose_at(int index, double pose_element);
  void set_velocity_vector(const Eigen::VectorXd& velocity);
  void set_velocity_at(int index, double velocity_element);

 private:
  std::unique_ptr<morphac::constructs::Pose> pose_;
  std::unique_ptr<morphac::constructs::Velocity> velocity_;
};

}  // namespace constructs
}  // namespace morphac

#endif
