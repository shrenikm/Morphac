#ifndef POSE_H
#define POSE_H

#include <sstream>
#include <vector>

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class Pose {
 public:
  Pose(const int size);
  Pose(const Eigen::VectorXd& data);
  Pose(std::initializer_list<double> elements);

  // Copy constructor.
  Pose(const Pose& pose) = default;

  // Copy assignment.
  Pose& operator=(const Pose& pose) = default;

  Pose& operator+=(const Pose& pose);
  Pose operator+(const Pose& pose) const;
  Pose& operator-=(const Pose& pose);
  Pose operator-(const Pose& pose) const;
  Pose& operator*=(const double scalar);

  friend bool operator==(const Pose& pose1, const Pose& pose2);
  friend bool operator!=(const Pose& pose1, const Pose& pose2);

  double& operator()(const int index);
  double operator()(const int index) const;

  friend std::ostream& operator<<(std::ostream& os, const Pose& pose);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  int get_size() const;
  const Eigen::VectorXd& get_data() const;
  void set_data(const Eigen::VectorXd& data);
  void set_data(std::initializer_list<double> elements);

  bool IsEmpty() const;
  static Pose CreateLike(const morphac::constructs::Pose& pose);

 private:
  int size_;
  Eigen::VectorXd data_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
Pose operator*(Pose pose, const double scalar);
Pose operator*(const double scalar, Pose pose);

}  // namespace constructs
}  // namespace morphac

#endif

