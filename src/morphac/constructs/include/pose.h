#ifndef POSE_H
#define POSE_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class Pose {
 public:
  Pose(int size);
  Pose(Eigen::VectorXd pose_vector);
  Pose(const Pose& pose);

  const int get_size() const;
  const Eigen::VectorXd& get_pose_vector() const;
  double get_pose_at(int index) const;
  void set_pose_vector(const Eigen::VectorXd& pose_vector);
  void set_pose_at(int index, double pose_element);

 private:
  const int size_;
  Eigen::VectorXd pose_vector_;
};

}  // namespace constructs
}  // namespace morphac

#endif

