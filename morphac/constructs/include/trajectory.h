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
  Trajectory(const Eigen::MatrixXd& data);
  Trajectory(std::initializer_list<std::initializer_list<double>> elements);

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

  morphac::constructs::State& operator()(const int index);
  morphac::constructs::State operator()(const int index) const;

  friend std::ostream& operator<<(std::ostream& os,
                                  const Trajectory& trajectory);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  const Eigen::MatrixXd& get_data() const;

  void set_data(const Eigen::MatrixXd& data);
  void set_data(std::initializer_list<std::initializer_list<double>> elements);

  void AddPoint(const morphac::constructs& State state, const int index = -1);
  void AddPoint(std::initializer_list<double> elements, const int index = -1);

  void RemovePoint(const int index);
  void RemovePoints(std::vector<const int> indices);

 private:
  int dim_;
  Eigen::MatrixXd data_;
};

}  // namespace constructs
}  // namespace morphac
