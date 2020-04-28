#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/state.h"

namespace {

using std::initializer_list;
using std::make_unique;
using std::ostringstream;
using std::srand;
using std::unique_ptr;
using std::vector;

using Eigen::VectorXd;

using morphac::constructs::Pose;
using morphac::constructs::State;
using morphac::constructs::Velocity;

class StateTest : public ::testing::Test {
 protected:
  StateTest() {
    state1_ = make_unique<State>(3, 2);
    state2_ = make_unique<State>(VectorXd::Zero(4), VectorXd::Zero(2));
    state3_ = make_unique<State>(initializer_list<double>{0, 0},
                                 initializer_list<double>{0, 0, 0});
    state4_ = make_unique<State>(Pose(1), Velocity(5));
  }

  void SetUp() override {
    // Set random seed for Eigen.
    srand(7);
  }

  unique_ptr<State> state1_, state2_, state3_, state4_;
};

TEST_F(StateTest, CopyConstructor) {
  State state1(*state1_);

  VectorXd state_vector = VectorXd::Random(10);
  State state2(state_vector.head(6), state_vector.tail(4));
  State state3(state2);

  ASSERT_TRUE(state1.get_state_vector().isApprox(VectorXd::Zero(5)));
  ASSERT_TRUE(state3.get_state_vector().isApprox(state_vector));
}

TEST_F(StateTest, ConstState) {
  const State state(3, 3);

  // We should be able to obtain const Pose and const Velocity objects from
  // this const state (these are read-only).
  ASSERT_TRUE(state.get_pose().get_pose_vector().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(
      state.get_velocity().get_velocity_vector().isApprox(VectorXd::Zero(3)));

  // For a const State, the values can only be accessed but not set, as a
  // reference (lvalue) is not returned for this overload of the operator.
  for (int i = 0; i < state.get_size(); ++i) {
    ASSERT_EQ(state(i), 0);
  }

  // After const casting to a non-const, we should be able to modify the Pose
  // and Velocity.
  const_cast<State&>(state).get_pose().set_pose_vector(VectorXd::Ones(3));
  const_cast<State&>(state).get_velocity().set_velocity_vector(
      VectorXd::Ones(3));
  ASSERT_TRUE(state.get_pose().get_pose_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(
      state.get_velocity().get_velocity_vector().isApprox(VectorXd::Ones(3)));
}

TEST_F(StateTest, EmptyAndPartialConstruction) {
  State state1(0, 0);
  State state2(1, 0);
  State state3(0, 1);

  ASSERT_TRUE(state1.IsEmpty());
  // Both Pose and Velocity have to be empty.
  ASSERT_TRUE(state1.IsPoseEmpty());
  ASSERT_TRUE(state1.IsVelocityEmpty());
  ASSERT_TRUE(state1.IsEmpty());

  ASSERT_FALSE(state2.IsPoseEmpty());
  ASSERT_TRUE(state2.IsVelocityEmpty());
  ASSERT_FALSE(state2.IsEmpty());

  ASSERT_TRUE(state3.IsPoseEmpty());
  ASSERT_FALSE(state3.IsVelocityEmpty());
  ASSERT_FALSE(state3.IsEmpty());

  // Other ways of constructing an empty state.
  ASSERT_TRUE(State({}, {}).IsEmpty());
  ASSERT_TRUE(State(VectorXd::Zero(0), VectorXd::Zero(0)).IsEmpty());

  // Accessors are invalid for empty Pose and Velocity components. These
  // are checked indirectly through Pose and Velocity.

  ASSERT_THROW(state1.get_pose_vector(), std::logic_error);
  ASSERT_THROW(state1.get_velocity_vector(), std::logic_error);
  ASSERT_THROW(state1.set_pose_vector(VectorXd::Zero(0)), std::logic_error);
  ASSERT_THROW(state1.set_velocity_vector(VectorXd::Zero(0)), std::logic_error);
  ASSERT_THROW(state1(0), std::out_of_range);

  ASSERT_TRUE(state2.get_pose_vector().isApprox(VectorXd::Zero(1)));
  ASSERT_THROW(state2.get_velocity_vector(), std::logic_error);

  state2.set_pose_vector({1});
  ASSERT_TRUE(state2.get_pose_vector().isApprox(VectorXd::Ones(1)));
  ASSERT_THROW(state2.set_velocity_vector(VectorXd::Zero(0)), std::logic_error);

  ASSERT_THROW(state3.get_pose_vector(), std::logic_error);
  ASSERT_TRUE(state3.get_velocity_vector().isApprox(VectorXd::Zero(1)));

  ASSERT_THROW(state3.set_pose_vector(VectorXd::Zero(0)), std::logic_error);
  state3.set_velocity_vector({1});
  ASSERT_TRUE(state3.get_velocity_vector().isApprox(VectorXd::Ones(1)));
}

TEST_F(StateTest, Sizes) {
  ASSERT_EQ(state1_->get_size_pose(), 3);
  ASSERT_EQ(state1_->get_size_velocity(), 2);
  ASSERT_EQ(state1_->get_size(), 5);

  ASSERT_EQ(state2_->get_size_pose(), 4);
  ASSERT_EQ(state2_->get_size_velocity(), 2);
  ASSERT_EQ(state2_->get_size(), 6);

  ASSERT_EQ(state3_->get_size_pose(), 2);
  ASSERT_EQ(state3_->get_size_velocity(), 3);
  ASSERT_EQ(state3_->get_size(), 5);

  ASSERT_EQ(state4_->get_size_pose(), 1);
  ASSERT_EQ(state4_->get_size_velocity(), 5);
  ASSERT_EQ(state4_->get_size(), 6);

  // Partial and empty states.
  ASSERT_EQ(State(0, 0).get_size_pose(), 0);
  ASSERT_EQ(State(0, 0).get_size_velocity(), 0);

  ASSERT_EQ(State(3, 0).get_size_pose(), 3);
  ASSERT_EQ(State(3, 0).get_size_velocity(), 0);

  ASSERT_EQ(State(0, 2).get_size_pose(), 0);
  ASSERT_EQ(State(0, 2).get_size_velocity(), 2);
}

TEST_F(StateTest, GetPose) {
  // Make sure that we can get the pose from the state.
  ASSERT_EQ(state1_->get_pose().get_size(), 3);
  ASSERT_TRUE(state1_->get_pose_vector().isApprox(VectorXd::Zero(3)));

  ASSERT_EQ(state2_->get_pose().get_size(), 4);
  ASSERT_TRUE(state2_->get_pose_vector().isApprox(VectorXd::Zero(4)));

  ASSERT_EQ(state3_->get_pose().get_size(), 2);
  ASSERT_TRUE(state3_->get_pose_vector().isApprox(VectorXd::Zero(2)));

  ASSERT_EQ(state4_->get_pose().get_size(), 1);
  ASSERT_TRUE(state4_->get_pose_vector().isApprox(VectorXd::Zero(1)));

  // Testing that the returned pose is a reference and can be modified.
  Pose& pose1 = state1_->get_pose();
  pose1.set_pose_vector(VectorXd::Ones(3));
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(state1_->get_pose_vector().isApprox(VectorXd::Ones(3)));

  Pose& pose2 = state2_->get_pose();
  pose2.set_pose_vector(VectorXd::Ones(4));
  ASSERT_TRUE(pose2.get_pose_vector().isApprox(VectorXd::Ones(4)));
  ASSERT_TRUE(state2_->get_pose_vector().isApprox(VectorXd::Ones(4)));

  Pose& pose3 = state3_->get_pose();
  pose3.set_pose_vector(VectorXd::Ones(2));
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(VectorXd::Ones(2)));
  ASSERT_TRUE(state3_->get_pose_vector().isApprox(VectorXd::Ones(2)));

  Pose& pose4 = state4_->get_pose();
  pose4.set_pose_vector(VectorXd::Ones(1));
  ASSERT_TRUE(pose4.get_pose_vector().isApprox(VectorXd::Ones(1)));
  ASSERT_TRUE(state4_->get_pose_vector().isApprox(VectorXd::Ones(1)));

  // For a partial (pose empty) state, accessing the pose should throw an
  // exception.
  ASSERT_THROW(State(0, 3).get_pose(), std::logic_error);
}

TEST_F(StateTest, GetVelocity) {
  // Make sure that we can get the velocity from the state.
  ASSERT_EQ(state1_->get_velocity().get_size(), 2);
  ASSERT_TRUE(state1_->get_velocity_vector().isApprox(VectorXd::Zero(2)));

  ASSERT_EQ(state2_->get_velocity().get_size(), 2);
  ASSERT_TRUE(state2_->get_velocity_vector().isApprox(VectorXd::Zero(2)));

  ASSERT_EQ(state3_->get_velocity().get_size(), 3);
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(VectorXd::Zero(3)));

  ASSERT_EQ(state4_->get_velocity().get_size(), 5);
  ASSERT_TRUE(state4_->get_velocity_vector().isApprox(VectorXd::Zero(5)));

  // Testing that the returned velocity is a reference and can be modified.
  Velocity& velocity1 = state1_->get_velocity();
  velocity1.set_velocity_vector(VectorXd::Ones(2));
  ASSERT_TRUE(velocity1.get_velocity_vector().isApprox(VectorXd::Ones(2)));
  ASSERT_TRUE(state1_->get_velocity_vector().isApprox(VectorXd::Ones(2)));

  Velocity& velocity2 = state2_->get_velocity();
  velocity2.set_velocity_vector(VectorXd::Ones(2));
  ASSERT_TRUE(velocity2.get_velocity_vector().isApprox(VectorXd::Ones(2)));
  ASSERT_TRUE(state2_->get_velocity_vector().isApprox(VectorXd::Ones(2)));

  Velocity& velocity3 = state3_->get_velocity();
  velocity3.set_velocity_vector(VectorXd::Ones(3));
  ASSERT_TRUE(velocity3.get_velocity_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(VectorXd::Ones(3)));

  Velocity& velocity4 = state4_->get_velocity();
  velocity4.set_velocity_vector(VectorXd::Ones(5));
  ASSERT_TRUE(velocity4.get_velocity_vector().isApprox(VectorXd::Ones(5)));
  ASSERT_TRUE(state4_->get_velocity_vector().isApprox(VectorXd::Ones(5)));

  // For a partial (velocity empty) state, accessing the velocity should throw
  // an exception.
  ASSERT_THROW(State(3, 0).get_velocity(), std::logic_error);
}

TEST_F(StateTest, GetPoseVector) {
  ASSERT_TRUE(state1_->get_pose_vector().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(state2_->get_pose_vector().isApprox(VectorXd::Zero(4)));
  ASSERT_TRUE(state3_->get_pose_vector().isApprox(VectorXd::Zero(2)));
  ASSERT_TRUE(state4_->get_pose_vector().isApprox(VectorXd::Zero(1)));

  // Arbitrary State.
  VectorXd pose_vector = VectorXd::Random(6);
  State state(pose_vector, VectorXd::Zero(2));

  ASSERT_TRUE(state.get_pose_vector().isApprox(pose_vector));

  // For a partial (pose empty) state, accessing the pose vector should throw an
  // error
  ASSERT_THROW(State(0, 3).get_pose_vector(), std::logic_error);
}

TEST_F(StateTest, GetVelocityVector) {
  ASSERT_TRUE(state1_->get_velocity_vector().isApprox(VectorXd::Zero(2)));
  ASSERT_TRUE(state2_->get_velocity_vector().isApprox(VectorXd::Zero(2)));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(state4_->get_velocity_vector().isApprox(VectorXd::Zero(5)));

  // Arbitrary State.
  VectorXd velocity_vector = VectorXd::Random(6);
  State state(VectorXd::Zero(2), velocity_vector);

  ASSERT_TRUE(state.get_velocity_vector().isApprox(velocity_vector));

  // For a partial (velocity empty) state, accessing the velocity vector should
  // throw an error
  ASSERT_THROW(State(3, 0).get_velocity_vector(), std::logic_error);
}

TEST_F(StateTest, GetStateVector) {
  ASSERT_TRUE(state1_->get_state_vector().isApprox(VectorXd::Zero(5)));
  ASSERT_TRUE(state2_->get_state_vector().isApprox(VectorXd::Zero(6)));
  ASSERT_TRUE(state3_->get_state_vector().isApprox(VectorXd::Zero(5)));
  ASSERT_TRUE(state4_->get_state_vector().isApprox(VectorXd::Zero(6)));

  // Arbitrary State.
  VectorXd pose_vector = VectorXd::Random(7);
  VectorXd velocity_vector = VectorXd::Random(6);
  VectorXd state_vector(13);
  state_vector << pose_vector, velocity_vector;
  State state(pose_vector, velocity_vector);

  ASSERT_TRUE(state.get_state_vector().isApprox(state_vector));

  // For an empty state, accessing the state vector should throw an error.
  ASSERT_THROW(State(0, 0).get_state_vector(), std::logic_error);
}

TEST_F(StateTest, GetStateAt) {
  for (int i = 0; i < state1_->get_size(); ++i) {
    ASSERT_EQ((*state1_)(i), 0);
  }
  for (int i = 0; i < state2_->get_size(); ++i) {
    ASSERT_EQ((*state2_)(i), 0);
  }
  for (int i = 0; i < state3_->get_size(); ++i) {
    ASSERT_EQ((*state3_)(i), 0);
  }
  for (int i = 0; i < state4_->get_size(); ++i) {
    ASSERT_EQ((*state4_)(i), 0);
  }

  // Arbitrary State.
  VectorXd pose_vector = VectorXd::Random(7);
  VectorXd velocity_vector = VectorXd::Random(6);
  VectorXd state_vector(13);
  state_vector << pose_vector, velocity_vector;
  State state(pose_vector, velocity_vector);

  for (int i = 0; i < state.get_size(); ++i) {
    ASSERT_EQ(state(i), state_vector(i));
  }

  // Partial States.
  VectorXd partial_pose_vector = VectorXd::Random(3);
  VectorXd partial_velocity_vector = VectorXd::Random(2);
  State partial_state1(partial_pose_vector, VectorXd::Zero(0));
  State partial_state2(VectorXd::Zero(0), partial_velocity_vector);

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(partial_state1(i), partial_pose_vector(i));
  }

  for (int i = 0; i < 2; ++i) {
    ASSERT_EQ(partial_state2(i), partial_velocity_vector(i));
  }

  // Invalid get at.
  ASSERT_THROW((*state1_)(-1), std::out_of_range);
  ASSERT_THROW((*state1_)(5), std::out_of_range);

  ASSERT_THROW((*state2_)(-1), std::out_of_range);
  ASSERT_THROW((*state2_)(6), std::out_of_range);

  ASSERT_THROW((*state3_)(-1), std::out_of_range);
  ASSERT_THROW((*state3_)(5), std::out_of_range);

  ASSERT_THROW((*state4_)(-1), std::out_of_range);
  ASSERT_THROW((*state4_)(6), std::out_of_range);

  ASSERT_THROW(partial_state1(-1), std::out_of_range);
  ASSERT_THROW(partial_state1(3), std::out_of_range);

  ASSERT_THROW(partial_state2(-1), std::out_of_range);
  ASSERT_THROW(partial_state2(2), std::out_of_range);
}

TEST_F(StateTest, SetPose) {
  state1_->set_pose(Pose(VectorXd::Ones(3)));
  ASSERT_TRUE(state1_->get_pose_vector().isApprox(VectorXd::Ones(3)));

  state2_->set_pose(Pose(VectorXd::Ones(4)));
  ASSERT_TRUE(state2_->get_pose_vector().isApprox(VectorXd::Ones(4)));

  state3_->set_pose(Pose(VectorXd::Ones(2)));
  ASSERT_TRUE(state3_->get_pose_vector().isApprox(VectorXd::Ones(2)));

  state4_->set_pose(Pose({1}));
  ASSERT_TRUE(state4_->get_pose_vector().isApprox(VectorXd::Ones(1)));

  // Invalid pose setting.
  ASSERT_THROW(state1_->set_pose(Pose(2)), std::invalid_argument);
  ASSERT_THROW(state1_->set_pose(Pose(4)), std::invalid_argument);

  ASSERT_THROW(state2_->set_pose(Pose(3)), std::invalid_argument);
  ASSERT_THROW(state2_->set_pose(Pose(5)), std::invalid_argument);

  ASSERT_THROW(state3_->set_pose(Pose(1)), std::invalid_argument);
  ASSERT_THROW(state3_->set_pose(Pose(3)), std::invalid_argument);

  ASSERT_THROW(state4_->set_pose(Pose(0)), std::invalid_argument);
  ASSERT_THROW(state4_->set_pose(Pose(2)), std::invalid_argument);

  // Setting a pose to a partial (pose empty) state must throw an error.
  ASSERT_THROW(State(0, 3).set_pose(Pose(1)), std::logic_error);
  ASSERT_THROW(State(0, 3).set_pose(Pose(0)), std::logic_error);
}

TEST_F(StateTest, SetVelocity) {
  state1_->set_velocity(Velocity(VectorXd::Ones(2)));
  ASSERT_TRUE(state1_->get_velocity_vector().isApprox(VectorXd::Ones(2)));

  state2_->set_velocity(Velocity(VectorXd::Ones(2)));
  ASSERT_TRUE(state2_->get_velocity_vector().isApprox(VectorXd::Ones(2)));

  state3_->set_velocity(Velocity(VectorXd::Ones(3)));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(VectorXd::Ones(3)));

  state4_->set_velocity(Velocity({1, 1, 1, 1, 1}));
  ASSERT_TRUE(state4_->get_velocity_vector().isApprox(VectorXd::Ones(5)));

  // Invalid velocity setting.
  ASSERT_THROW(state1_->set_velocity(Velocity(1)), std::invalid_argument);
  ASSERT_THROW(state1_->set_velocity(Velocity(3)), std::invalid_argument);

  ASSERT_THROW(state2_->set_velocity(Velocity(1)), std::invalid_argument);
  ASSERT_THROW(state2_->set_velocity(Velocity(3)), std::invalid_argument);

  ASSERT_THROW(state3_->set_velocity(Velocity(2)), std::invalid_argument);
  ASSERT_THROW(state3_->set_velocity(Velocity(4)), std::invalid_argument);

  ASSERT_THROW(state4_->set_velocity(Velocity(4)), std::invalid_argument);
  ASSERT_THROW(state4_->set_velocity(Velocity(6)), std::invalid_argument);

  // Setting a velocity to a partial (velocity empty) state must throw an error.
  ASSERT_THROW(State(3, 0).set_velocity(Velocity(1)), std::logic_error);
  ASSERT_THROW(State(3, 0).set_velocity(Velocity(0)), std::logic_error);
}

TEST_F(StateTest, SetPoseVector) {
  // Checking if the pose can be set and also if the velocity is unchanged.
  state1_->set_pose_vector(VectorXd::Ones(3));
  ASSERT_TRUE(state1_->get_pose_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(state1_->get_velocity_vector().isApprox(VectorXd::Zero(2)));

  state2_->set_pose_vector(VectorXd::Ones(4));
  ASSERT_TRUE(state2_->get_pose_vector().isApprox(VectorXd::Ones(4)));
  ASSERT_TRUE(state2_->get_velocity_vector().isApprox(VectorXd::Zero(2)));

  state3_->set_pose_vector(VectorXd::Ones(2));
  ASSERT_TRUE(state3_->get_pose_vector().isApprox(VectorXd::Ones(2)));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(VectorXd::Zero(3)));

  state4_->set_pose_vector(VectorXd::Ones(1));
  ASSERT_TRUE(state4_->get_pose_vector().isApprox(VectorXd::Ones(1)));
  ASSERT_TRUE(state4_->get_velocity_vector().isApprox(VectorXd::Zero(5)));

  // Arbitrary state pose.
  VectorXd pose_vector(5);
  pose_vector << 1, -2, 3, -4, 5.5;
  State state(5, 5);
  state.set_pose_vector({1, -2, 3, -4, 5.5});
  ASSERT_TRUE(state.get_pose_vector().isApprox(pose_vector));
  ASSERT_TRUE(state.get_velocity_vector().isApprox(VectorXd::Zero(5)));

  // Invalid set.
  ASSERT_THROW(state1_->set_pose_vector(VectorXd::Zero(2)),
               std::invalid_argument);
  ASSERT_THROW(state1_->set_pose_vector(VectorXd::Zero(4)),
               std::invalid_argument);

  ASSERT_THROW(state2_->set_pose_vector(VectorXd::Zero(3)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_pose_vector(VectorXd::Zero(5)),
               std::invalid_argument);

  ASSERT_THROW(state3_->set_pose_vector(VectorXd::Zero(1)),
               std::invalid_argument);
  ASSERT_THROW(state3_->set_pose_vector(VectorXd::Zero(3)),
               std::invalid_argument);

  ASSERT_THROW(state4_->set_pose_vector(VectorXd::Zero(0)),
               std::invalid_argument);
  ASSERT_THROW(state4_->set_pose_vector(VectorXd::Zero(2)),
               std::invalid_argument);

  // Setting a pose vector to a partial (pose empty) state must throw an error.
  ASSERT_THROW(State(0, 3).set_pose_vector(VectorXd::Zero(1)),
               std::logic_error);
  ASSERT_THROW(State(0, 3).set_pose_vector(VectorXd::Zero(0)),
               std::logic_error);
}

TEST_F(StateTest, SetVelocityVector) {
  // Checking if the velocity can be set and also if the pose is unchanged.
  state1_->set_velocity_vector(VectorXd::Ones(2));
  ASSERT_TRUE(state1_->get_pose_vector().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(state1_->get_velocity_vector().isApprox(VectorXd::Ones(2)));

  state2_->set_velocity_vector(VectorXd::Ones(2));
  ASSERT_TRUE(state2_->get_pose_vector().isApprox(VectorXd::Zero(4)));
  ASSERT_TRUE(state2_->get_velocity_vector().isApprox(VectorXd::Ones(2)));

  state3_->set_velocity_vector(VectorXd::Ones(3));
  ASSERT_TRUE(state3_->get_pose_vector().isApprox(VectorXd::Zero(2)));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(VectorXd::Ones(3)));

  state4_->set_velocity_vector(VectorXd::Ones(5));
  ASSERT_TRUE(state4_->get_pose_vector().isApprox(VectorXd::Zero(1)));
  ASSERT_TRUE(state4_->get_velocity_vector().isApprox(VectorXd::Ones(5)));

  // Arbitrary state velocity.
  VectorXd velocity_vector(5);
  velocity_vector << 1, -2, 3, -4, 5.5;
  State state(5, 5);
  state.set_velocity_vector({1, -2, 3, -4, 5.5});
  ASSERT_TRUE(state.get_pose_vector().isApprox(VectorXd::Zero(5)));
  ASSERT_TRUE(state.get_velocity_vector().isApprox(velocity_vector));

  // Invalid set.
  ASSERT_THROW(state1_->set_velocity_vector(VectorXd::Zero(1)),
               std::invalid_argument);
  ASSERT_THROW(state1_->set_velocity_vector(VectorXd::Zero(3)),
               std::invalid_argument);

  ASSERT_THROW(state2_->set_velocity_vector(VectorXd::Zero(1)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_velocity_vector(VectorXd::Zero(3)),
               std::invalid_argument);

  ASSERT_THROW(state3_->set_velocity_vector(VectorXd::Zero(2)),
               std::invalid_argument);
  ASSERT_THROW(state3_->set_velocity_vector(VectorXd::Zero(4)),
               std::invalid_argument);

  ASSERT_THROW(state4_->set_velocity_vector(VectorXd::Zero(4)),
               std::invalid_argument);
  ASSERT_THROW(state4_->set_velocity_vector(VectorXd::Zero(6)),
               std::invalid_argument);

  // Setting a velocity vector to a partial (velocity empty) state must throw an
  // error.
  ASSERT_THROW(State(3, 0).set_velocity_vector(VectorXd::Zero(1)),
               std::logic_error);
  ASSERT_THROW(State(3, 0).set_velocity_vector(VectorXd::Zero(0)),
               std::logic_error);
}

TEST_F(StateTest, SetStateVector) {
  // Make sure that when the state is set, it sets both pose and velocity.
  state1_->set_state_vector(VectorXd::Ones(5));
  ASSERT_TRUE(state1_->get_pose_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(state1_->get_velocity_vector().isApprox(VectorXd::Ones(2)));
  ASSERT_TRUE(state1_->get_state_vector().isApprox(VectorXd::Ones(5)));

  state2_->set_state_vector(VectorXd::Ones(6));
  ASSERT_TRUE(state2_->get_pose_vector().isApprox(VectorXd::Ones(4)));
  ASSERT_TRUE(state2_->get_velocity_vector().isApprox(VectorXd::Ones(2)));
  ASSERT_TRUE(state2_->get_state_vector().isApprox(VectorXd::Ones(6)));

  state3_->set_state_vector(VectorXd::Ones(5));
  ASSERT_TRUE(state3_->get_pose_vector().isApprox(VectorXd::Ones(2)));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(state3_->get_state_vector().isApprox(VectorXd::Ones(5)));

  state4_->set_state_vector(VectorXd::Ones(6));
  ASSERT_TRUE(state4_->get_pose_vector().isApprox(VectorXd::Ones(1)));
  ASSERT_TRUE(state4_->get_velocity_vector().isApprox(VectorXd::Ones(5)));
  ASSERT_TRUE(state4_->get_state_vector().isApprox(VectorXd::Ones(6)));

  // Aribitrary state.
  VectorXd pose_vector(5), velocity_vector(5), state_vector(10);
  pose_vector << 1, -2, 3, -4, 5.5;
  velocity_vector << -1, 2, -3, 4, -5.5;
  state_vector << pose_vector, velocity_vector;

  State state(5, 5);
  state.set_state_vector({1, -2, 3, -4, 5.5, -1, 2, -3, 4, -5.5});
  ASSERT_TRUE(state.get_pose_vector().isApprox(pose_vector));
  ASSERT_TRUE(state.get_velocity_vector().isApprox(velocity_vector));
  ASSERT_TRUE(state.get_state_vector().isApprox(state_vector));

  // Invalid set.
  ASSERT_THROW(state1_->set_state_vector(VectorXd::Zero(4)),
               std::invalid_argument);
  ASSERT_THROW(state1_->set_state_vector(VectorXd::Zero(6)),
               std::invalid_argument);

  ASSERT_THROW(state2_->set_state_vector(VectorXd::Zero(5)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_velocity_vector(VectorXd::Zero(7)),
               std::invalid_argument);

  ASSERT_THROW(state3_->set_state_vector(VectorXd::Zero(4)),
               std::invalid_argument);
  ASSERT_THROW(state3_->set_state_vector(VectorXd::Zero(6)),
               std::invalid_argument);

  ASSERT_THROW(state4_->set_state_vector(VectorXd::Zero(5)),
               std::invalid_argument);
  ASSERT_THROW(state4_->set_state_vector(VectorXd::Zero(7)),
               std::invalid_argument);

  // Setting a state vector to an empty state must throw an error.
  ASSERT_THROW(State(0, 0).set_state_vector(VectorXd::Zero(1)),
               std::logic_error);
  ASSERT_THROW(State(0, 0).set_state_vector(VectorXd::Zero(0)),
               std::logic_error);
}

TEST_F(StateTest, Addition) {
  VectorXd p1(3), p2(3), v1(2), v2(2);
  VectorXd d1(5), d2(5);
  VectorXd s1(5), s2(5);
  p1 << 1, 2, 3;
  p2 << 3, 2, 1;
  v1 << -1, 0;
  v2 << -2, 4;
  s1 << p1, v1;
  s2 << p2, v2;
  d1 << 4, 4, 4, -3, 4;
  d2 << 7, 6, 5, -5, 8;

  State state1{p1, v1};
  State state2{p2, v2};

  // Trivial addition.
  state1 += State::CreateLike(state1);
  ASSERT_TRUE(state1.get_state_vector().isApprox(s1));

  state1 = state1 + State::CreateLike(state1);
  ASSERT_TRUE(state1.get_state_vector().isApprox(s1));

  // Non trivial addition.
  state1 += state2;
  ASSERT_TRUE(state1.get_state_vector().isApprox(d1));

  State state3 = state1 + state2;
  ASSERT_TRUE(state3.get_state_vector().isApprox(d2));

  State state4 = state2 + state1;
  ASSERT_TRUE(state3.get_state_vector().isApprox(state4.get_state_vector()));

  // Throw an error if trying to add incompatible States.
  ASSERT_THROW(State(3, 2) + State(2, 3), std::invalid_argument);
  ASSERT_THROW(State(3, 2) + State(3, 1), std::invalid_argument);
  ASSERT_THROW(State(3, 2) + State(2, 2), std::invalid_argument);
}

TEST_F(StateTest, PartialAddition) {
  VectorXd res1(3);
  res1 << 1, -1, 1;

  // We've already all the kinds of operations in the Addition test, so here
  // only test if the partial states can be added properly.
  ASSERT_TRUE((State({1, 2, 3}, {}) + State({0, -3, -2}, {}))
                  .get_pose_vector()
                  .isApprox(res1));
  ASSERT_TRUE((State({1, 2, 3}, {}) + State({0, -3, -2}, {}))
                  .get_state_vector()
                  .isApprox(res1));

  ASSERT_TRUE((State({}, {1, 2, 3}) + State({}, {0, -3, -2}))
                  .get_velocity_vector()
                  .isApprox(res1));
  ASSERT_TRUE((State({}, {1, 2, 3}) + State({}, {0, -3, -2}))
                  .get_state_vector()
                  .isApprox(res1));

  // Throw an error if trying to add incompatible partial states.
  ASSERT_THROW(State(3, 0) + State(2, 0), std::invalid_argument);
  ASSERT_THROW(State(3, 0) + State(3, 1), std::invalid_argument);
  ASSERT_THROW(State(0, 3) + State(0, 2), std::invalid_argument);
  ASSERT_THROW(State(0, 3) + State(1, 3), std::invalid_argument);
}

TEST_F(StateTest, Subtraction) {
  VectorXd p1(3), p2(3), v1(2), v2(2);
  VectorXd d1(5), d2(5);
  VectorXd s1(5), s2(5);
  p1 << 1, 2, 3;
  p2 << 3, 2, 1;
  v1 << -1, 0;
  v2 << -2, 4;
  s1 << p1, v1;
  s2 << p2, v2;
  d1 << -2, 0, 2, 1, -4;
  d2 << -5, -2, 1, 3, -8;

  State state1{p1, v1};
  State state2{p2, v2};

  // Trivial subtraction.
  state1 -= State::CreateLike(state1);
  ASSERT_TRUE(state1.get_state_vector().isApprox(s1));

  state1 = state1 - State::CreateLike(state1);
  ASSERT_TRUE(state1.get_state_vector().isApprox(s1));

  // Non trivial subtraction.
  state1 -= state2;
  ASSERT_TRUE(state1.get_state_vector().isApprox(d1));

  State state3 = state1 - state2;
  ASSERT_TRUE(state3.get_state_vector().isApprox(d2));

  State state4 = state2 - state1;
  ASSERT_TRUE(
      state3.get_state_vector().isApprox(-1 * state4.get_state_vector()));

  // Throw an error if trying to subtract incompatible States.
  ASSERT_THROW(State(3, 2) - State(2, 3), std::invalid_argument);
  ASSERT_THROW(State(3, 2) - State(3, 1), std::invalid_argument);
  ASSERT_THROW(State(3, 2) - State(2, 2), std::invalid_argument);
}

TEST_F(StateTest, PartialSubtraction) {
  VectorXd res1(3);
  res1 << 1, -1, 1;

  // We've already all the kinds of operations in the Subtraction test, so here
  // only test if the partial states can be subtracted properly.
  ASSERT_TRUE((State({1, 2, 3}, {}) - State({0, 3, 2}, {}))
                  .get_pose_vector()
                  .isApprox(res1));
  ASSERT_TRUE((State({1, 2, 3}, {}) - State({0, 3, 2}, {}))
                  .get_state_vector()
                  .isApprox(res1));

  ASSERT_TRUE((State({}, {1, 2, 3}) - State({}, {0, 3, 2}))
                  .get_velocity_vector()
                  .isApprox(res1));
  ASSERT_TRUE((State({}, {1, 2, 3}) - State({}, {0, 3, 2}))
                  .get_state_vector()
                  .isApprox(res1));

  // Throw an error if trying to add incompatible partial states.
  ASSERT_THROW(State(3, 0) - State(2, 0), std::invalid_argument);
  ASSERT_THROW(State(3, 0) - State(3, 1), std::invalid_argument);
  ASSERT_THROW(State(0, 3) - State(0, 2), std::invalid_argument);
  ASSERT_THROW(State(0, 3) - State(1, 3), std::invalid_argument);
}

TEST_F(StateTest, Multiplication) {
  VectorXd p1(3), p2(3), v1(2), v2(2);
  VectorXd d1(5), d2(5);
  VectorXd s1(5), s2(5);
  p1 << 1, 2, 3;
  p2 << 3, 2, 1;
  v1 << -1, 0;
  v2 << -2, 4;
  s1 << p1, v1;
  s2 << p2, v2;
  d1 << 2, 4, 6, -2, 0;
  d2 << -3, -2, -1, 2, -4;

  State state1{p1, v1};
  State state2{p2, v2};

  // Trivial multiplication.
  state1 = state1 * 1.0;
  ASSERT_TRUE(state1.get_state_vector().isApprox(s1));
  ASSERT_TRUE((0.0 * state1).get_state_vector().isApprox(VectorXd::Zero(5)));

  // Non trivial multiplication.
  state1 *= 2.0;
  ASSERT_TRUE(state1.get_state_vector().isApprox(d1));

  State state3 = state2 * -1.0;
  State state4 = -1 * state2;
  ASSERT_TRUE(state3.get_state_vector().isApprox(d2));
  ASSERT_TRUE(state4.get_state_vector().isApprox(d2));
}

TEST_F(StateTest, PartialMultiplication) {
  VectorXd res1(3);
  res1 << 1, 2, 3;

  // We've already all the kinds of operations in the Multiplication test, so
  // here only test if the partial states can be multiplied properly.
  ASSERT_TRUE((State({1, 2, 3}, {}) * 1.0).get_pose_vector().isApprox(res1));
  ASSERT_TRUE((State({1, 2, 3}, {}) * 1.0).get_state_vector().isApprox(res1));

  ASSERT_TRUE(
      (State({}, {1, 2, 3}) * 1.0).get_velocity_vector().isApprox(res1));
  ASSERT_TRUE((State({}, {1, 2, 3}) * 1.0).get_state_vector().isApprox(res1));
}

TEST_F(StateTest, Equality) {
  ASSERT_TRUE(State(3, 2) == State(3, 2));
  ASSERT_TRUE(State(3, 2) == State(VectorXd::Zero(3), VectorXd::Zero(2)));
  ASSERT_TRUE(State(VectorXd::Ones(2), VectorXd::Ones(3)) ==
              State({1, 1}, {1, 1, 1}));
  ASSERT_TRUE(State({1, 2, 3}, {4, 5}) == State({1, 2, 3}, {4, 5}));

  ASSERT_TRUE(State(3, 2) != State(2, 3));
  ASSERT_TRUE(State(3, 2) != State(3, 3));
  ASSERT_TRUE(State(3, 2) != State(2, 2));
  ASSERT_TRUE(State(3, 2) != State(VectorXd::Zero(2), VectorXd::Zero(3)));
  ASSERT_TRUE(State(3, 2) != State(VectorXd::Zero(3), VectorXd::Zero(3)));
  ASSERT_TRUE(State(3, 2) != State(VectorXd::Zero(2), VectorXd::Zero(2)));
  ASSERT_TRUE(State(3, 2) != State({0, 0}, {0, 0, 0}));
  ASSERT_TRUE(State(3, 2) != State({0, 0, 0}, {0, 0, 0}));
  ASSERT_TRUE(State(3, 2) != State({0, 0}, {0, 0}));
  ASSERT_TRUE(State({1, 2}, {3, 4}) != State({5, 6}, {7, 8}));
  ASSERT_TRUE(State({1, 2}, {3, 4}) != State({1, 2}, {3, 4.000001}));
}

TEST_F(StateTest, PartialEquality) {
  ASSERT_TRUE(State(3, 0) == State(3, 0));
  ASSERT_TRUE(State(3, 0) == State(VectorXd::Zero(3), VectorXd::Zero(0)));
  ASSERT_TRUE(State(VectorXd::Ones(2), VectorXd::Ones(0)) == State({1, 1}, {}));
  ASSERT_TRUE(State({1, 2, 3}, {}) == State({1, 2, 3}, {}));
  ASSERT_TRUE(State(0, 3) == State(0, 3));
  ASSERT_TRUE(State(0, 3) == State(VectorXd::Zero(0), VectorXd::Zero(3)));
  ASSERT_TRUE(State(VectorXd::Ones(0), VectorXd::Ones(2)) == State({}, {1, 1}));
  ASSERT_TRUE(State({}, {1, 2, 3}) == State({}, {1, 2, 3}));

  ASSERT_TRUE(State(3, 0) != State(3, 1));
  ASSERT_TRUE(State(3, 0) != State(2, 0));
  ASSERT_TRUE(State(3, 0) != State(VectorXd::Zero(3), VectorXd::Zero(1)));
  ASSERT_TRUE(State(3, 0) != State(VectorXd::Zero(2), VectorXd::Zero(0)));
  ASSERT_TRUE(State(3, 0) != State({0, 0, 0}, {0}));
  ASSERT_TRUE(State(3, 0) != State({0, 0}, {}));
  ASSERT_TRUE(State({1, 2, 3}, {}) != State({4, 5, 6}, {}));
  ASSERT_TRUE(State({1, 2, 3}, {}) != State({1, 2, 3.000001}, {}));

  ASSERT_TRUE(State(0, 3) != State(1, 3));
  ASSERT_TRUE(State(0, 3) != State(0, 2));
  ASSERT_TRUE(State(0, 3) != State(VectorXd::Zero(1), VectorXd::Zero(3)));
  ASSERT_TRUE(State(0, 3) != State(VectorXd::Zero(0), VectorXd::Zero(2)));
  ASSERT_TRUE(State(0, 3) != State({0}, {0, 0, 0}));
  ASSERT_TRUE(State(0, 3) != State({}, {0, 0}));
  ASSERT_TRUE(State({}, {1, 2, 3}) != State({}, {4, 5, 6}));
  ASSERT_TRUE(State({}, {1, 2, 3}) != State({}, {1, 2, 3.000001}));
}

TEST_F(StateTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << (*state1_);

  // Multiple state object representations in the stream.
  os << " " << (*state3_) << std::endl;

  // Test representation of partially constructed state.
  os << " " << State(3, 0) << " " << State(0, 2);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

