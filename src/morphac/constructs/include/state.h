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
  State(const int size_pose = 0, const int size_velocity = 0);
  State(const Eigen::VectorXd& pose_vector,
        const Eigen::VectorXd& velocity_vector);
  State(const morphac::constructs::Pose& pose,
        const morphac::constructs::Velocity& velocity);

  State& operator+=(const State& state);
  State operator+(const State& state) const;
  State& operator-=(const State& state);
  State operator-(const State& state) const;
  State& operator*=(const double scalar);

  double& operator()(const int index);
  double operator()(const int index) const;

  int get_size_pose() const;
  int get_size_velocity() const;
  int get_size() const;

  // Pose and Velocity accessors for const and non-const States.
  morphac::constructs::Pose& get_pose();
  const morphac::constructs::Pose& get_pose() const;
  morphac::constructs::Velocity& get_velocity();
  const morphac::constructs::Velocity& get_velocity() const;

  const Eigen::VectorXd& get_pose_vector() const;
  const Eigen::VectorXd& get_velocity_vector() const;
  const Eigen::VectorXd get_state_vector() const;
  void set_pose_vector(const Eigen::VectorXd& pose_vector);
  void set_velocity_vector(const Eigen::VectorXd& velocity_vector);
  void set_state_vector(const Eigen::VectorXd& state_vector);

  bool IsEmpty() const;
  bool IsPoseEmpty() const;
  bool IsVelocityEmpty() const;
  static State CreateLike(const morphac::constructs::State& state);

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
