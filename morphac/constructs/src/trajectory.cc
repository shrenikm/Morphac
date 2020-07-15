#include "constructs/include/trajectory.h"

namespace morphac {
namespace constructs {

using std::vector;

using Eigen::MatrixXd;

using morphac::constructs::State;

Trajectory::Trajectory(const State& initial_state)
    : dim_(initial_state.get_size()),
      size_(1),
      pose_size_(initial_state.get_pose_size()),
      velocity_size_(initial_state.get_velocity_size()),
      data_(initial_state.get_data()) {}

Trajectory::Trajectory(const MatrixXd& data, const int pose_size,
                       const int velocity_size)
    : dim_(data.cols()),
      size_(data.rows()),
      pose_size_(pose_size),
      velocity_size_(velocity_size),
      data_(data) {
  MORPH_REQUIRE(data.rows() > 0 && data.cols() > 0, std::invalid_argument,
                "Trajectory data must not have zero rows or columns.");
}

Trajectory& Trajectory::operator+=(const Trajectory& trajectory) {
  // Making sure they have the same dimensions and pose and velocity sizes.
  MORPH_REQUIRE(this->dim_ == trajectory.dim_, std::invalid_argument,
                "Trajectories do not have the same dimension. The += operator "
                "requires them to have the same dimension.");
  MORPH_REQUIRE(this->pose_size_ == trajectory.pose_size_,
                std::invalid_argument,
                "Trajectories do not have the same pose size. The += operator "
                "requires them to have the same pose sizes.");
  MORPH_REQUIRE(this->velocity_size_ == trajectory.velocity_size_,
                std::invalid_argument,
                "Trajectories do not have the same velocity size. The += "
                "operator requires them to have the same velocity sizes.");
  MatrixXd new_data(this->size_ + trajectory.size_, this->dim_);
  new_data << this->data_, trajectory.data_;
  this->data_ = new_data;
  // Update size.
  this->size_ = this->size_ + trajectory.size_;
  return *this;
}

Trajectory Trajectory::operator+(const Trajectory& trajectory) const {
  // Argument validation happens in the += function call.
  Trajectory result(*this);
  result += trajectory;
  return result;
}

//State& operator()(const int index) {
//  MORPH_REQUIRE(index >= 0 && index < this->size_, std::out_of_range,
//                "Trajectory index out of range.");
//  return State
//}

}  // namespace constructs
}  // namespace morphac
