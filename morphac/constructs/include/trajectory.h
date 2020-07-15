#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <sstream>
#include <vector>

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"
#include "constructs/include/state.h"

namespace morphac {
namespace constructs {

class Trajectory {
 public:
  Trajectory(const morphac::constructs::State& initial_state);
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
  morphac::constructs::State operator()(const int index) const;

  friend std::ostream& operator<<(std::ostream& os,
                                  const Trajectory& trajectory);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  const Eigen::MatrixXd& get_data() const;

  void set_data(const Eigen::MatrixXd& data);

  void AddKnotPoint(const morphac::constructs::State& state,
                    const int index = -1);
  void AddKnotPoints(std::vector<morphac::constructs::State> states,
                     const int index = -1);

  void RemoveKnotPoint(const int index);
  void RemoveKnotPoints(std::vector<const int> indices);

  void ReplaceKnotPoint(const morphac::constructs::State& state,
                        const int index);
  void ReplaceKnotPoints(const morphac::constructs::State& state,
                         std::vector<const int> indices);

 private:
  // Dim is constant for a trajectory once it is defined. Even if the entire
  // data of the trajectory is changed, it must maintain the original dimension.
  // This is because dim is the identity of the trajectory and changing this
  // probably warrants the creation of a new Trajectory object.
  int dim_;
  int size_;
  int pose_size_;
  int velocity_size_;
  Eigen::MatrixXd data_;
};

}  // namespace constructs
}  // namespace morphac

#endif
