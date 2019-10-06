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

  int get_size();
  Eigen::VectorXd get_pose();
  double get_pose(int index);
  void set_pose(Eigen::VectorXd pose);
  void set_pose(int index, double pose_element);

 private:
  int size_;
  Eigen::VectorXd pose_;
};

}  // namespace constructs
}  // namespace morphac

#endif

