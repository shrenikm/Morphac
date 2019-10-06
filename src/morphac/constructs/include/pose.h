#ifndef POSE_H
#define POSE_H

#include "Eigen/Dense"

#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace constructs {

class Pose {
 public:
  Pose(int size);
  Pose(Eigen::VectorXd pose);
  Pose(const Pose& pose);

  int get_size() const;
  const Eigen::VectorXd& get_pose() const;
  double get_pose(int index) const;
  void set_pose(const Eigen::VectorXd& pose);
  void set_pose(int index, double pose_element);

 private:
  const int size_;
  Eigen::VectorXd pose_;
};

}  // namespace constructs
}  // namespace morphac

#endif

