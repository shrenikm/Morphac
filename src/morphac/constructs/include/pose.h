#ifndef POSE_H
#define POSE_H

#include "Eigen/Dense"

#include "common/include/error_macros.h"

namespace morphac {
namespace constructs {

class Pose {
 public:
  Pose(int size);
  Pose(Eigen::VectorXd pose);

  int get_size();
  Eigen::VectorXd get_pose();
  double get_pose(int index);
  void set_pose(Eigen::VectorXd pose);
  void set_pose(double pose_element, int index);

 private:
  int size_;
  Eigen::VectorXd pose_;
};

}  // namespace constructs
}  // namespace morphac

#endif

