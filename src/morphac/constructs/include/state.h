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
  // Sometimes the state may only include the poses. In such cases the velocity
  // part in the constructor may be skipped.
  State(const int size_pose, const int size_velocity);
  State(const Eigen::VectorXd& pose_vector,
        const Eigen::VectorXd& velocity_vector);
  State(const morphac::constructs::Pose& pose,
        const morphac::constructs::Velocity& velocity);

  State& operator+=(const State& state);
  State operator+(const State& state);
  State& operator-=(const State& state);
  State operator-(const State& state);
  State& operator*=(const double scalar);

  double& operator()(const int index);

  bool is_empty() const;
  bool is_pose_empty() const;
  bool is_velocity_empty() const;

  const int get_size_pose() const;
  const int get_size_velocity() const;
  const int get_size() const;
  const morphac::constructs::Pose& get_pose() const;
  const morphac::constructs::Velocity& get_velocity() const;
  const Eigen::VectorXd& get_pose_vector() const;
  const Eigen::VectorXd& get_velocity_vector() const;
  const Eigen::VectorXd get_state_vector() const;
  void set_pose_vector(const Eigen::VectorXd& pose_vector);
  void set_velocity_vector(const Eigen::VectorXd& velocity_vector);
  void set_state_vector(const Eigen::VectorXd& state_vector);

 private:
  morphac::constructs::Pose pose_;
  morphac::constructs::Velocity velocity_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
State operator*(const double scalar, State state);
State operator*(State state, const double scalar);

}  // namespace constructs
}  // namespace morphac

#endif
