#ifndef POSE_H
#define POSE_H

#include <sstream>

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class Pose {
 public:
  Pose(const int size = 0);
  Pose(const Eigen::VectorXd& pose_vector);
  // Copy constructor;
  Pose(const Pose& pose);

  Pose& operator+=(const Pose& pose);
  Pose operator+(const Pose& pose) const;
  Pose& operator-=(const Pose& pose);
  Pose operator-(const Pose& pose) const;
  Pose& operator*=(const double scalar);

  double& operator()(const int index);
  double operator()(const int index) const;

  friend std::ostream& operator<<(std::ostream& os, const Pose& pose);
  // String representation that uses the << overload.
  // This is what the python binding uses.
  std::string ToString() const;

  int get_size() const;
  const Eigen::VectorXd& get_pose_vector() const;
  void set_pose_vector(const Eigen::VectorXd& pose_vector);

  bool IsEmpty() const;
  static Pose CreateLike(const morphac::constructs::Pose& pose);

 private:
  const int size_;
  Eigen::VectorXd pose_vector_;
};

// Non-member multiplication operator functions to support lhs scalar
// multiplication
Pose operator*(Pose pose, const double scalar);
Pose operator*(const double scalar, Pose pose);

}  // namespace constructs
}  // namespace morphac

#endif

