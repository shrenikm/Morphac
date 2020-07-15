#include "constructs/include/trajectory.h"

namespace morphac {
namespace constructs {

using std::ostream;
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
  // Data matrix must be valid.
  MORPH_REQUIRE(data.rows() > 0 && data.cols() > 0, std::invalid_argument,
                "Trajectory data must not have zero rows or columns.");
  // pose_size + velocity_dim must equal dim.
  MORPH_REQUIRE(data.rows() == pose_size + velocity_size, std::invalid_argument,
                "Trajectory data and pose/velocity sizes are incompatible.");
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

bool operator==(const Trajectory& trajectory1, const Trajectory& trajectory2) {
  // Two trajectories are equal if all of their member values are equal.
  if ((trajectory1.dim_ == trajectory2.dim_) &&
      (trajectory1.size_ == trajectory2.size_) &&
      (trajectory1.pose_size_ == trajectory2.pose_size_) &&
      (trajectory1.data_.isApprox(trajectory2.data_, 1e-6))) {
    return true;
  }
  return false;
}

bool operator!=(const Trajectory& trajectory1, const Trajectory& trajectory2) {
  return !(trajectory1 == trajectory2);
}

State Trajectory::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < this->size_, std::out_of_range,
                "Trajectory index out of range.");
  return State(data_.row(index).head(pose_size_),
               data_.row(index).tail(velocity_size_));
}

ostream& operator<<(ostream& os, const Trajectory& trajectory) {
  os << "Trajectory[\n";
  for (int i = 0; i < size_; ++i) {
    os << "\t" << State(data_.row(i), pose_size_, velocity_size_) << "\n";
  }
  os << "]";
  return os;
}

string Trajectory::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

}  // namespace constructs
}  // namespace morphac