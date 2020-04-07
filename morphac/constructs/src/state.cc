#include "constructs/include/state.h"

namespace morphac {
namespace constructs {

using std::make_unique;
using std::move;
using std::ostream;
using std::ostringstream;
using std::string;
using std::unique_ptr;

using Eigen::VectorXd;

using morphac::constructs::Pose;
using morphac::constructs::Velocity;

State::State(const int size_pose, const int size_velocity)
    : pose_(Pose(size_pose)), velocity_(Velocity(size_velocity)) {
  // The Pose and Velocity constructors take care of invalid arguments.
}

State::State(const VectorXd& pose_vector, const VectorXd& velocity_vector)
    : pose_(Pose(pose_vector)), velocity_(Velocity(velocity_vector)) {
  // The Pose and Velocity constructors take care of invalid arguments.
}

State::State(const Pose& pose, const Velocity& velocity)
    : pose_(pose), velocity_(velocity) {}

State::State(const State& state)
    : pose_(state.pose_), velocity_(state.velocity_) {
  // We don't need to verify the input as an invalid State object cannot be
  // constructed.
}


State& State::operator+=(const State& state) {
  MORPH_REQUIRE(
      this->get_size_pose() == state.get_size_pose() &&
          this->get_size_velocity() == state.get_size_velocity(),
      std::invalid_argument,
      "States are not of the same size. The += operator requires them "
      "to be of the "
      "same size.");
  // The pose and velocities are added and set if they are non empty. If they
  // are empty, the default empty objects are kept as is and the resulting
  // pose/vector is also empty.
  if (!IsPoseEmpty()) {
    this->set_pose_vector(this->get_pose_vector() + state.get_pose_vector());
  }
  if (!IsVelocityEmpty()) {
    this->set_velocity_vector(this->get_velocity_vector() +
                              state.get_velocity_vector());
  }
  return *this;
}

State State::operator+(const State& state) const {
  MORPH_REQUIRE(this->get_size_pose() == state.get_size_pose() &&
                    this->get_size_velocity() == state.get_size_velocity(),
                std::invalid_argument,
                "States are not of the same size. The + operator requires them "
                "to be of the "
                "same size.");
  State result(this->get_size_pose(), this->get_size_velocity());
  // The pose and velocities are added and set if they are non empty. If they
  // are empty, the default empty objects are kept as is and the resulting
  // pose/vector is also empty.
  if (!IsPoseEmpty()) {
    result.set_pose_vector(this->get_pose_vector() + state.get_pose_vector());
  }
  if (!IsVelocityEmpty()) {
    result.set_velocity_vector(this->get_velocity_vector() +
                               state.get_velocity_vector());
  }
  return result;
}

State& State::operator-=(const State& state) {
  MORPH_REQUIRE(
      this->get_size_pose() == state.get_size_pose() &&
          this->get_size_velocity() == state.get_size_velocity(),
      std::invalid_argument,
      "States are not of the same size. The -= operator requires them "
      "to be of the "
      "same size.");
  // The pose and velocities are subtracted and set if they are non empty. If
  // they are empty, the default empty objects are kept as is and the resulting
  // pose/vector is also empty.
  if (!IsPoseEmpty()) {
    this->set_pose_vector(this->get_pose_vector() - state.get_pose_vector());
  }
  if (!IsVelocityEmpty()) {
    this->set_velocity_vector(this->get_velocity_vector() -
                              state.get_velocity_vector());
  }
  return *this;
}

State State::operator-(const State& state) const {
  MORPH_REQUIRE(this->get_size_pose() == state.get_size_pose() &&
                    this->get_size_velocity() == state.get_size_velocity(),
                std::invalid_argument,
                "States are not of the same size. The - operator requires them "
                "to be of the "
                "same size.");
  State result(this->get_size_pose(), this->get_size_velocity());
  // The pose and velocities are subtracted and set if they are non empty. If
  // they are empty, the default empty objects are kept as is and the resulting
  // pose/vector is also empty.
  if (!IsPoseEmpty()) {
    result.set_pose_vector(this->get_pose_vector() - state.get_pose_vector());
  }
  if (!IsVelocityEmpty()) {
    result.set_velocity_vector(this->get_velocity_vector() -
                               state.get_velocity_vector());
  }
  return result;
}

State& State::operator*=(const double scalar) {
  // The pose and velocities are multiplied and set if they are non empty. If
  // they are empty, the default empty objects are kept as is and the resulting
  // pose/vector is also empty.
  if (!IsPoseEmpty()) {
    this->set_pose_vector(this->get_pose_vector() * scalar);
  }
  if (!IsVelocityEmpty()) {
    this->set_velocity_vector(this->get_velocity_vector() * scalar);
  }
  return *this;
}

//// Non-member multiplication functions
State operator*(State state, const double scalar) { return state *= scalar; }

State operator*(const double scalar, State state) { return state *= scalar; }

double& State::operator()(const int index) {
  MORPH_REQUIRE(index >= 0 && index < get_size(), std::out_of_range,
                "Pose index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "State object is empty");
  // If the index corresponds to the pose
  if (index < get_size_pose()) {
    return pose_(index);
  } else {
    // Index corresponds to velocity
    return velocity_(index - get_size_pose());
  }
}

double State::operator()(const int index) const {
  MORPH_REQUIRE(index >= 0 && index < get_size(), std::out_of_range,
                "Pose index out of bounds.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "State object is empty");
  // If the index corresponds to the pose
  if (index < get_size_pose()) {
    return pose_(index);
  } else {
    // Index corresponds to velocity
    return velocity_(index - get_size_pose());
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

int State::get_size_pose() const { return pose_.get_size(); }

int State::get_size_velocity() const { return velocity_.get_size(); }

int State::get_size() const { return pose_.get_size() + velocity_.get_size(); }

Pose& State::get_pose() { return pose_; }

const Pose& State::get_pose() const { return pose_; }

Velocity& State::get_velocity() { return velocity_; }

const Velocity& State::get_velocity() const { return velocity_; }

const VectorXd& State::get_pose_vector() const {
  return pose_.get_pose_vector();
}

const VectorXd& State::get_velocity_vector() const {
  return velocity_.get_velocity_vector();
}

const VectorXd State::get_state_vector() const {
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "State object is empty");
  VectorXd state_vector(get_size());
  VectorXd pose_vector = VectorXd::Zero(0);
  VectorXd velocity_vector = VectorXd::Zero(0);

  // Populating if not empty.
  if (!IsPoseEmpty()) {
    pose_vector = get_pose_vector();
  }
  if (!IsVelocityEmpty()) {
    velocity_vector = get_velocity_vector();
  }
  state_vector << pose_vector, velocity_vector;
  return state_vector;
}

void State::set_pose_vector(const VectorXd& pose_vector) {
  // The Pose class setter does the argument check.
  pose_.set_pose_vector(pose_vector);
}

void State::set_velocity_vector(const VectorXd& velocity_vector) {
  // The Velocity class getter does the argument check.
  velocity_.set_velocity_vector(velocity_vector);
}

void State::set_state_vector(const VectorXd& state_vector) {
  // Need to check if the dimensions are correct
  MORPH_REQUIRE(state_vector.size() == get_size(), std::invalid_argument,
                "State vector size is incorrect.");
  MORPH_REQUIRE(!IsEmpty(), std::logic_error, "State object is empty");
  if (!IsPoseEmpty()) {
    set_pose_vector(state_vector.head(get_size_pose()));
  }
  if (!IsVelocityEmpty()) {
    set_velocity_vector(state_vector.tail(get_size_velocity()));
  }
}

State State::CreateLike(const State& state) {
  State new_state{state.get_size_pose(), state.get_size_velocity()};
  return new_state;
}

}  // constructs
}  // morphac
