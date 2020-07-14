#include "constructs/include/trajectory.h"

namespace morphac {
namespace constructs {

using std::vector;

using Eigen::MatrixXd;

using morphac::constructs::State;

Trajectory::Trajectory(const State& initial_state)
    : dim_(initial_state.get_size()), data_(initial_state.get_data()) {}

Trajectory::Trajectory(const MatrixXd& data) : dim_(data.cols()), data_(data) {
  MORPH_REQUIRE(data.rows() > 0 && data.cols() > 0, std::invalid_argument,
                "Trajectory data must not have zero rows or columns.");
}

Trajectory& Trajectory::operator+=(const Trajectory& trajectory) {
  MORPH_REQUIRE(this->dim_ == trajectory.dim_, std::invalid_argument,
                "Trajectories do not have the same dimension. The += operator "
                "requires them to have the same dimension.");
  MatrixXd new_data(this->data_.rows() + trajectory.data_.rows(), this->dim_);
  new_data << this->data_, trajectory.data_;
  this->data_ = new_data;
  return *this;
}

Trajectory Trajectory::operator+(const Trajectory& trajectory) const {
  MORPH_REQUIRE(this->dim_ == trajectory.dim_, std::invalid_argument,
                "Trajectories do not have the same dimension. The + operator "
                "requires them to have the same dimension.");
  Trajectory result(this->data_);
  result += trajectory;
  return result;
}

}  // namespace constructs
}  // namespace morphac
