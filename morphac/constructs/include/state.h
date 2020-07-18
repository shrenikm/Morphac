#ifndef STATE_H
#define STATE_H

#include <sstream>
#include <vector>

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
  State(const Eigen::VectorXd& pose_data, const Eigen::VectorXd& velocity_data);
  State(std::initializer_list<double> pose_elements,
        std::initializer_list<double> velocity_elements);
  State(const morphac::constructs::Pose& pose,
        const morphac::constructs::Velocity& velocity);

  // Copy constructor.
  State(const State& state) = default;

  // Copy assignment.
  State& operator=(const State& state) = default;

  State& operator+=(const State& state);
  State operator+(const State& state) const;
  State& operator-=(const State& state);
  State operator-(const State& state) const;
  State& operator*=(const double scalar);

  friend bool operator==(const State& state1, const State& state2);
  friend bool operator!=(const State& state1, const State& state2);

  double& operator()(const int index);
  const double& operator()(const int index) const;

  friend std::ostream& operator<<(std::ostream& os, const State& state);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  int get_pose_size() const;
  int get_velocity_size() const;
  int get_size() const;

  // Pose and Velocity accessors for const and non-const States.
  morphac::constructs::Pose& get_pose();
  const morphac::constructs::Pose& get_pose() const;
  morphac::constructs::Velocity& get_velocity();
  const morphac::constructs::Velocity& get_velocity() const;

  const Eigen::VectorXd& get_pose_data() const;
  const Eigen::VectorXd& get_velocity_data() const;
  const Eigen::VectorXd get_data() const;

  void set_pose(const morphac::constructs::Pose& pose);
  void set_velocity(const morphac::constructs::Velocity& velocity);

  void set_pose_data(const Eigen::VectorXd& pose_data);
  void set_pose_data(std::initializer_list<double> pose_elements);
  void set_velocity_data(const Eigen::VectorXd& velocity_data);
  void set_velocity_data(std::initializer_list<double> velocity_elements);
  void set_data(const Eigen::VectorXd& data);
  void set_data(std::initializer_list<double> elements);

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
State operator*(State state, const double scalar);
State operator*(const double scalar, State state);

}  // namespace constructs
}  // namespace morphac

#endif
