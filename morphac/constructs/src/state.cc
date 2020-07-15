#include "constructs/include/state.h"

namespace morphac {
namespace constructs {

using std::initializer_list;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

using Eigen::Map;
using Eigen::VectorXd;

using morphac::constructs::Pose;
using morphac::constructs::Velocity;

State::State(const int size_pose, const int size_velocity)
    : pose_(Pose(size_pose)), velocity_(Velocity(size_velocity)) {
  // The Pose and Velocity constructors take care of invalid arguments.
}

State::State(const VectorXd& pose_data, const VectorXd& velocity_data)
    : pose_(Pose(pose_data)), velocity_(Velocity(velocity_data)) {
  // The Pose and Velocity constructors take care of invalid arguments.
}

State::State(initializer_list<double> pose_elements,
             initializer_list<double> velocity_elements)
    // Temporary initialization as we Pose and Velocity don't have defaults.
    // TODO: Make this cleaner.
    : pose_(Pose(pose_elements.size())),
      velocity_(Velocity(velocity_elements)) {
  // As they are initializers, the size always going to be >= 0 and need not
  // be checked.
  vector<double> pose_data_vector(pose_elements);
  vector<double> velocity_data_vector(velocity_elements);

  pose_ = Pose(Map<VectorXd>(&pose_data_vector[0], pose_elements.size()));
  velocity_ = Velocity(
      Map<VectorXd>(&velocity_data_vector[0], velocity_elements.size()));
}

State::State(const Pose& pose, const Velocity& velocity)
    : pose_(pose), velocity_(velocity) {}

State& State::operator+=(const State& state) {
  MORPH_REQUIRE(
      this->get_pose_size() == state.get_pose_size() &&
          this->get_velocity_size() == state.get_velocity_size(),
      std::invalid_argument,
      "States are not of the same size. The += operator requires them "
      "to be of the "
      "same size.");
  // The pose and velocities are added and set if they are non empty. If they
  // are empty, the default empty objects are kept as is and the resulting
  // pose/velocity is also empty.
  if (!IsPoseEmpty()) {
    this->set_pose_data(this->get_pose_data() + state.get_pose_data());
  }
  if (!IsVelocityEmpty()) {
    this->set_velocity_data(this->get_velocity_data() +
                            state.get_velocity_data());
  }
  return *this;
}

State State::operator+(const State& state) const {
  // Argument validation happens in the += function call.
  State result(*this);
  result += state;
  return result;
}

State& State::operator-=(const State& state) {
  MORPH_REQUIRE(
      this->get_pose_size() == state.get_pose_size() &&
          this->get_velocity_size() == state.get_velocity_size(),
      std::invalid_argument,
      "States are not of the same size. The -= operator requires them "
      "to be of the "
      "same size.");
  // The pose and velocities are subtracted and set if they are non empty. If
  // they are empty, the default empty objects are kept as is and the resulting
  // pose/velocity is also empty.
  if (!IsPoseEmpty()) {
    this->set_pose_data(this->get_pose_data() - state.get_pose_data());
  }
  if (!IsVelocityEmpty()) {
    this->set_velocity_data(this->get_velocity_data() -
                            state.get_velocity_data());
  }
  return *this;
}

State State::operator-(const State& state) const {
  // Argument validation happens in the += function call.
  State result(*this);
  result -= state;
  return result;
}

State& State::operator*=(const double scalar) {
  // The pose and velocities are multiplied and set if they are non empty. If
  // they are empty, the default empty objects are kept as is and the resulting
  // pose/velocity is also empty.
  if (!IsPoseEmpty()) {
    this->set_pose_data(this->get_pose_data() * scalar);
  }
  if (!IsVelocityEmpty()) {
    this->set_velocity_data(this->get_velocity_data() * scalar);
  }
  return *this;
}

//// Non-member multiplication functions
State operator*(State state, const double scalar) { return state *= scalar; }

State operator*(const double scalar, State state) { return state *= scalar; }

bool operator==(const State& state1, const State& state2) {
  // Two states are equal if their pose and velocity sizes and data values are
  // equal. This is equivalent to their their corresponding pose and velocity
  // components being equal to each other.
  if (state1.pose_ == state2.pose_ && state1.velocity_ == state2.velocity_) {
    return true;
  }
  return false;
}

bool operator!=(const State& state1, const State& state2) {
  return !(state1 == state2);
}

double& State::operator()(const int index) {
  MORPH_REQUIRE(index >= 0 && index < get_size(), std::out_of_range,
                "State index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "State object is empty.");
  // If the index corresponds to the pose
  if (index < get_pose_size()) {
    return pose_(index);
  } else {
    // Index corresponds to velocity
    return velocity_(index - get_pose_size());
  }
}

double State::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < get_size(), std::out_of_range,
                "State index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "State object is empty.");
  // If the index corresponds to the pose
  if (index < get_pose_size()) {
    return pose_(index);
  } else {
    // Index corresponds to velocity
    return velocity_(index - get_pose_size());
  }
}

ostream& operator<<(ostream& os, const State& state) {
  // Handling partial construction representation. The State representation
  // should be one of the following:
  // State[Pose, Velocity]
  // State[Pose]
  // State[Velocity]
  ostringstream internal;
  if (!state.IsPoseEmpty()) {
    // Non empty Pose
    if (!state.IsVelocityEmpty()) {
      // Non empty Pose and Velocity
      internal << state.get_pose() << ", " << state.get_velocity();
    } else {
      // Non empty Pose but empty velocity
      internal << state.get_pose();
    }
  } else {
    // Empty Pose
    if (!state.IsVelocityEmpty()) {
      // Empty Pose but non empty velocity
      internal << state.get_velocity();
    } else {
      // Empty Pose and Velocity
    }
  }

  os << "State[" << internal.str() << "]";
  return os;
}

string State::ToString() const {
  ostringstream os;
  os << *this;
  return os.str();
}

bool State::IsEmpty() const { return IsPoseEmpty() && IsVelocityEmpty(); }

bool State::IsPoseEmpty() const { return pose_.IsEmpty(); }

bool State::IsVelocityEmpty() const { return velocity_.IsEmpty(); }

int State::get_pose_size() const { return pose_.get_size(); }

int State::get_velocity_size() const { return velocity_.get_size(); }

int State::get_size() const { return pose_.get_size() + velocity_.get_size(); }

Pose& State::get_pose() {
  // We return only if the pose is non empty.
  MORPH_REQUIRE(!pose_.IsEmpty(), std::logic_error, "Pose component is empty.");
  return pose_;
}

const Pose& State::get_pose() const {
  // We return only if the pose is non empty.
  MORPH_REQUIRE(!pose_.IsEmpty(), std::logic_error, "Pose component is empty.");
  return pose_;
}

Velocity& State::get_velocity() {
  // We return only if the velocity is non empty.
  MORPH_REQUIRE(!velocity_.IsEmpty(), std::logic_error,
                "Velocity component is empty.");
  return velocity_;
}

const Velocity& State::get_velocity() const {
  // We return only if the velocity is non empty.
  MORPH_REQUIRE(!velocity_.IsEmpty(), std::logic_error,
                "Velocity component is empty.");
  return velocity_;
}

const VectorXd& State::get_pose_data() const {
  // We return the pose data only if the pose is non empty.
  MORPH_REQUIRE(!pose_.IsEmpty(), std::logic_error, "Pose component is empty.");
  return pose_.get_data();
}

const VectorXd& State::get_velocity_data() const {
  // We return the velocity data only if the velocity is non empty.
  MORPH_REQUIRE(!velocity_.IsEmpty(), std::logic_error,
                "Velocity component is empty.");
  return velocity_.get_data();
}

void State::set_pose(const Pose& pose) {
  MORPH_REQUIRE(pose_.get_size() == pose.get_size(), std::invalid_argument,
                "Pose dimensions do not match.");
  MORPH_REQUIRE(!pose.IsEmpty(), std::logic_error, "Pose object is empty.");
  pose_ = pose;
}

void State::set_velocity(const Velocity& velocity) {
  MORPH_REQUIRE(velocity_.get_size() == velocity.get_size(),
                std::invalid_argument, "Velocity dimensions do not match.");
  MORPH_REQUIRE(!velocity.IsEmpty(), std::logic_error,
                "Velocity object is empty.");
  velocity_ = velocity;
}

const VectorXd State::get_data() const {
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "State is empty.");
  VectorXd data(get_size());
  VectorXd pose_data = VectorXd::Zero(0);
  VectorXd velocity_data = VectorXd::Zero(0);

  // Populating if not empty.
  if (!IsPoseEmpty()) {
    pose_data = get_pose_data();
  }
  if (!IsVelocityEmpty()) {
    velocity_data = get_velocity_data();
  }
  data << pose_data, velocity_data;
  return data;
}

void State::set_pose_data(const VectorXd& pose_data) {
  // We allow setting only if the pose is non empty.
  MORPH_REQUIRE(!pose_.IsEmpty(), std::logic_error, "Pose component is empty.");

  // The Pose class setter does the argument dimension check.
  pose_.set_data(pose_data);
}

void State::set_pose_data(initializer_list<double> pose_elements) {
  // We allow setting only if the pose is non empty.
  MORPH_REQUIRE(!pose_.IsEmpty(), std::logic_error, "Pose component is empty.");

  // The Pose class setter does the argument check.
  pose_.set_data(pose_elements);
}

void State::set_velocity_data(const VectorXd& velocity_data) {
  // We allow setting only if the velocity is non empty.
  MORPH_REQUIRE(!velocity_.IsEmpty(), std::logic_error,
                "Velocity component is empty.");

  // The Velocity class getter does the argument check.
  velocity_.set_data(velocity_data);
}

void State::set_velocity_data(initializer_list<double> velocity_elements) {
  // We allow setting only if the velocity is non empty.
  MORPH_REQUIRE(!velocity_.IsEmpty(), std::logic_error,
                "Velocity component is empty.");

  // The Velocity class getter does the argument check.
  velocity_.set_data(velocity_elements);
}

void State::set_data(const VectorXd& data) {
  // Need to check if the dimensions are correct
  MORPH_REQUIRE(data.size() == get_size(), std::invalid_argument,
                "State data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "State object is empty.");
  if (!IsPoseEmpty()) {
    set_pose_data(data.head(get_pose_size()));
  }
  if (!IsVelocityEmpty()) {
    set_velocity_data(data.tail(get_velocity_size()));
  }
}

void State::set_data(initializer_list<double> elements) {
  // Need to check if the dimensions are correct
  MORPH_REQUIRE((int)elements.size() == get_size(), std::invalid_argument,
                "State data size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "State object is empty.");

  vector<double> data_vector(elements);
  VectorXd data = Map<VectorXd>(&data_vector[0], get_size());

  if (!IsPoseEmpty()) {
    set_pose_data(data.head(get_pose_size()));
  }
  if (!IsVelocityEmpty()) {
    set_velocity_data(data.tail(get_velocity_size()));
  }
}

State State::CreateLike(const State& state) {
  State new_state(state.get_pose_size(), state.get_velocity_size());
  return new_state;
}

}  // constructs
}  // morphac
