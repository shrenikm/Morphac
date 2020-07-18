#include "constructs/include/trajectory.h"

namespace morphac {
namespace constructs {

using std::greater;
using std::ostream;
using std::ostringstream;
using std::sort;
using std::string;
using std::vector;

using Eigen::MatrixXd;

using morphac::constructs::State;

void Trajectory::copy_data_to_knot_points(const MatrixXd& data) {
  // First we clear all of the existing points.
  knot_points_.clear();
  for (unsigned int i = 0; i < data.rows(); ++i) {
    knot_points_.push_back(
        State(data.row(i).head(pose_size_), data.row(i).tail(velocity_size_)));
  }
}

Trajectory::Trajectory(const State& state)
    : pose_size_(state.get_pose_size()),
      velocity_size_(state.get_velocity_size()) {
  MORPH_REQUIRE(!state.IsEmpty(), std::invalid_argument,
                "State must not be empty.");
  knot_points_.push_back(state);
}

Trajectory::Trajectory(const vector<State>& knot_points) {
  // First we make sure that the vector is not empty each state element has the
  // same dimensions.
  MORPH_REQUIRE(knot_points.size() > 0, std::invalid_argument,
                "Vector of knot points must not be empty.");
  for (auto& state : knot_points) {
    MORPH_REQUIRE(
        state.get_pose_size() == knot_points.at(0).get_pose_size() &&
            state.get_velocity_size() == knot_points.at(0).get_velocity_size(),
        std::invalid_argument,
        "Each state element needs to have the same pose and velocity sizes.");
  }
  pose_size_ = knot_points.at(0).get_pose_size();
  velocity_size_ = knot_points.at(0).get_velocity_size();
  knot_points_ = knot_points;
}

Trajectory::Trajectory(const MatrixXd& data, const int pose_size,
                       const int velocity_size)
    : pose_size_(pose_size), velocity_size_(velocity_size) {
  // Data matrix must be valid.
  MORPH_REQUIRE(data.rows() > 0 && data.cols() > 0, std::invalid_argument,
                "Trajectory data must not have zero rows or columns.");
  // pose_size + velocity_dim must equal dim.
  MORPH_REQUIRE(data.cols() == pose_size + velocity_size, std::invalid_argument,
                "Trajectory data and pose/velocity sizes are incompatible.");
  copy_data_to_knot_points(data);
}

Trajectory& Trajectory::operator+=(const Trajectory& trajectory) {
  // Making sure they have the same dimensions and pose and velocity sizes.
  MORPH_REQUIRE(this->get_dim() == trajectory.get_dim(), std::invalid_argument,
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
  this->knot_points_.insert(this->knot_points_.end(),
                            trajectory.knot_points_.begin(),
                            trajectory.knot_points_.end());
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
  if ((trajectory1.get_dim() != trajectory2.get_dim()) ||
      (trajectory1.get_size() != trajectory2.get_size()) ||
      (trajectory1.pose_size_ != trajectory2.pose_size_)) {
    return false;
  }
  for (int i = 0; i < trajectory1.get_size(); ++i) {
    if (trajectory1.knot_points_.at(i) != trajectory2.knot_points_.at(i)) {
      return false;
    }
  }

  return true;
}

bool operator!=(const Trajectory& trajectory1, const Trajectory& trajectory2) {
  return !(trajectory1 == trajectory2);
}

State& Trajectory::operator()(const int index) {
  MORPH_REQUIRE(index >= 0 && index < this->get_size(), std::out_of_range,
                "Trajectory index out of range.");
  return knot_points_.at(index);
}

const State& Trajectory::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < this->get_size(), std::out_of_range,
                "Trajectory index out of range.");
  return knot_points_.at(index);
}

ostream& operator<<(ostream& os, const Trajectory& trajectory) {
  os << "Trajectory[\n";
  for (int i = 0; i < trajectory.get_size(); ++i) {
    os << "\t" << trajectory.knot_points_.at(i) << "\n";
  }
  os << "]";
  return os;
}

string Trajectory::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

int Trajectory::get_dim() const { return pose_size_ + velocity_size_; }

int Trajectory::get_size() const { return knot_points_.size(); }

int Trajectory::get_pose_size() const { return pose_size_; }

int Trajectory::get_velocity_size() const { return velocity_size_; }

MatrixXd Trajectory::get_data() const {
  MatrixXd data(get_size(), get_dim());

  for (int i = 0; i < get_size(); ++i) {
    data.row(i) = knot_points_.at(i).get_data();
  }

  return data;
}

void Trajectory::set_data(const MatrixXd& data) {
  // The given data must have the right number of columns. The size of the
  // trajectory could be different.
  MORPH_REQUIRE(data.cols() == get_dim(), std::invalid_argument,
                "Trajectory data has an incompatible number of columns. The "
                "number of columns must equal the dimension of the "
                "Trajectory.");
  copy_data_to_knot_points(data);
}

void Trajectory::AddKnotPoint(const State& state, const int index) {
  // Make sure that the state is compatible.
  MORPH_REQUIRE(
      state.get_pose_size() == pose_size_ &&
          state.get_velocity_size() == velocity_size_,
      std::invalid_argument,
      "State's pose and velocity sizes do not match that of the trajectory.");
  // Making sure that the index is correct.
  MORPH_REQUIRE(index >= 0 && index <= get_size(), std::out_of_range,
                "Index out of bounds. Indices must lie in [0, size]");

  knot_points_.insert(knot_points_.begin() + index, state);
}

void Trajectory::AddKnotPoint(const State& state) {
  // If the index is not given, it means the given point needs to be added to
  // the end of the trajectory.
  // AddKnotPoint is called with index = size. The state validation is
  // done there.
  AddKnotPoint(state, get_size());
}

void Trajectory::AddKnotPoints(const vector<State>& states,
                               vector<int> indices) {
  // Making sure that both vectors have the same number of elements.
  MORPH_REQUIRE(states.size() == indices.size(), std::invalid_argument,
                "States and indices must have the same number of elements");

  // As the length of the vector changes as we keep inserting points, we cannot
  // do this in a loop directly.
  // We first sort the indices in ascending order, after which the points
  // can be inserted in loop.
  sort(indices.begin(), indices.end());

  for (unsigned int i = 0; i < states.size(); ++i) {
    // State validation is done in the AddKnotPoint function.
    AddKnotPoint(states.at(i), indices.at(i));
  }
}

void Trajectory::RemoveKnotPoint(const int index) {
  MORPH_REQUIRE(index >= 0 && index < get_size(), std::out_of_range,
                "Index out of bounds");
  knot_points_.erase(knot_points_.begin() + index);
}

void Trajectory::RemoveKnotPoints(vector<int> indices) {
  // Validity check for the indices happens in the RemoveKnotPoint function.

  // As the length of the vector changes as we keep removing points, we cannot
  // do this in a loop directly.
  // We first sort the indices in descending order, after which the points
  // can be removed in loop.
  sort(indices.begin(), indices.end(), greater<int>());
  for (unsigned int i = 0; i < indices.size(); ++i) {
    RemoveKnotPoint(indices.at(i));
  }
}

}  // namespace constructs
}  // namespace morphac
