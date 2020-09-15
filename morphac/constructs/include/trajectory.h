#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <algorithm>
#include <sstream>
#include <vector>

#include "Eigen/Dense"
#include "common/error_handling/include/error_macros.h"
#include "constructs/include/state.h"

namespace morphac {
namespace constructs {

class Trajectory {
 public:
  Trajectory(const morphac::constructs::State& knot_point);
  Trajectory(const std::vector<morphac::constructs::State>& knot_points);
  Trajectory(const Eigen::MatrixXd& data, const int pose_size,
             const int velocity_size);

  // Copy constructor.
  Trajectory(const Trajectory& trajectory) = default;

  // Copy assignment.
  Trajectory& operator=(const Trajectory& trajectory) = default;

  Trajectory& operator+=(const Trajectory& trajectory);
  Trajectory operator+(const Trajectory& trajectory) const;

  friend bool operator==(const Trajectory& trajectory1,
                         const Trajectory& trajectory2);
  friend bool operator!=(const Trajectory& trajectory1,
                         const Trajectory& trajectory2);

  // We don't allow for setting a trajectory point through the () operator as
  // we don't keep track of each row of the data matrix as a State object.
  // The ReplaceKnotPoint function needs to be used for this.
  morphac::constructs::State& operator[](const int index);
  const morphac::constructs::State& operator[](const int index) const;

  friend std::ostream& operator<<(std::ostream& os,
                                  const Trajectory& trajectory);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  int get_dim() const;
  int get_size() const;
  int get_pose_size() const;
  int get_velocity_size() const;
  Eigen::MatrixXd get_data() const;

  void set_data(const Eigen::MatrixXd& data);

  void AddKnotPoint(const morphac::constructs::State& knot_point,
                    const int index);
  void AddKnotPoint(const morphac::constructs::State& knot_point);
  void AddKnotPoints(const std::vector<morphac::constructs::State>& knot_points,
                     std::vector<int> indices);

  void RemoveKnotPoint(const int index);
  void RemoveKnotPoint();
  void RemoveKnotPoints(std::vector<int> indices);

 private:
  // Dim is constant for a trajectory once it is defined. Even if the entire
  // data of the trajectory is changed, it must maintain the original dimension.
  // This is because dim is the identity of the trajectory and changing this
  // probably warrants the creation of a new Trajectory object.

  void copy_data_to_knot_points(const Eigen::MatrixXd& data);

  int pose_size_;
  int velocity_size_;
  std::vector<morphac::constructs::State> knot_points_;
};

}  // namespace constructs
}  // namespace morphac

#endif
