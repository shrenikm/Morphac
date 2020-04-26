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

TEST_F(StateTest, EmptyConstruction) {
  State state1(0, 0);
  State state2(1, 0);
  State state3(0, 1);

  ASSERT_TRUE(state1.IsEmpty());
  // Both Pose and Velocity have to be empty.
  ASSERT_FALSE(state2.IsEmpty());
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

  // get_pose_vector for an empty pose is already tested for in pose_test.
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

  // get_velocity_vector for an empty velocity is already tested for in
  // velocity_test.
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
}

// TEST_F(StateTest, Addition) {
//  VectorXd p1(3), p2(3), v1(2), v2(2);
//  VectorXd d1(5), d2(5);
//  VectorXd s1(5), s2(5);
//  p1 << 1, 2, 3;
//  p2 << 3, 2, 1;
//  v1 << -1, 0;
//  v2 << -2, 4;
//  s1 << p1, v1;
//  s2 << p2, v2;
//  d1 << 4, 4, 4, -3, 4;
//  d2 << 7, 6, 5, -5, 8;
//
//  State state1{p1, v1};
//  State state2{p2, v2};
//
//  // Trivial addition.
//  state1 += State::CreateLike(state1);
//  ASSERT_TRUE(state1.get_state_vector().isApprox(s1));
//
//  state1 = state1 + State::CreateLike(state1);
//  ASSERT_TRUE(state1.get_state_vector().isApprox(s1));
//
//  state1 += state2;
//  ASSERT_TRUE(state1.get_state_vector().isApprox(d1));
//
//  State state3 = state1 + state2;
//  ASSERT_TRUE(state3.get_state_vector().isApprox(d2));
//
//  State state4 = state2 + state1;
//  ASSERT_TRUE(state3.get_state_vector().isApprox(state4.get_state_vector()));
//}
//
// TEST_F(StateTest, Subtraction) {
//  VectorXd p1(3), p2(3), v1(2), v2(2);
//  VectorXd d1(5), d2(5);
//  VectorXd s1(5), s2(5);
//  p1 << 1, 2, 3;
//  p2 << 3, 2, 1;
//  v1 << -1, 0;
//  v2 << -2, 4;
//  s1 << p1, v1;
//  s2 << p2, v2;
//  d1 << -2, 0, 2, 1, -4;
//  d2 << -5, -2, 1, 3, -8;
//
//  State state1{p1, v1};
//  State state2{p2, v2};
//
//  // Trivial subtraction.
//  state1 -= State::CreateLike(state1);
//  ASSERT_TRUE(state1.get_state_vector().isApprox(s1));
//
//  state1 = state1 - State::CreateLike(state1);
//  ASSERT_TRUE(state1.get_state_vector().isApprox(s1));
//
//  state1 -= state2;
//  ASSERT_TRUE(state1.get_state_vector().isApprox(d1));
//
//  State state3 = state1 - state2;
//  ASSERT_TRUE(state3.get_state_vector().isApprox(d2));
//
//  State state4 = state2 - state1;
//  ASSERT_TRUE(
//      state3.get_state_vector().isApprox(-1 * state4.get_state_vector()));
//}
//
// TEST_F(StateTest, Multiplication) {
//  VectorXd p1(3), p2(3), v1(2), v2(2);
//  VectorXd d1(5), d2(5);
//  VectorXd s1(5), s2(5);
//  p1 << 1, 2, 3;
//  p2 << 3, 2, 1;
//  v1 << -1, 0;
//  v2 << -2, 4;
//  s1 << p1, v1;
//  s2 << p2, v2;
//  d1 << 2, 4, 6, -2, 0;
//  d2 << -3, -2, -1, 2, -4;
//
//  State state1{p1, v1};
//  State state2{p2, v2};
//
//  // Trivial multiplication.
//  state1 = state1 * 1.0;
//  ASSERT_TRUE(state1.get_state_vector().isApprox(s1));
//  ASSERT_TRUE((0.0 * state1).get_state_vector().isApprox(VectorXd::Zero(5)));
//
//  state1 *= 2.0;
//  ASSERT_TRUE(state1.get_state_vector().isApprox(d1));
//
//  State state3 = state2 * -1.0;
//  State state4 = -1 * state2;
//  ASSERT_TRUE(state3.get_state_vector().isApprox(d2));
//  ASSERT_TRUE(state4.get_state_vector().isApprox(d2));
//}
//
// TEST_F(StateTest, StringRepresentation) {
//  // Testing that the << operator is overloaded properly.
//  // We don't test the actual string representation.
//  ostringstream os;
//  os << state1_;
//
//  // Multiple state object representations in the stream.
//  os << " " << state3_ << std::endl;
//
//  // Test representation of partially constructed state.
//  os << " " << State(Pose(3), Velocity(0)) << " "
//     << State(Pose(0), Velocity(2));
//}
//
// TEST_F(StateTest, PartialConstruction) {
//  // Constructing states without the velocity component.
//  State state1{3, 0};
//  State state2{VectorXd::Zero(4), VectorXd::Zero(0)};
//  State state3{Pose(5), Velocity()};
//
//  // Constructing states without the pose component.
//  State state4{0, 3};
//  State state5{VectorXd::Zero(0), VectorXd::Zero(4)};
//  State state6{Pose(), Velocity(5)};
//
//  // Both empty (empty state)
//  State state7{0, 0};
//
//  // Test emptiness.
//  ASSERT_TRUE(!state1.IsEmpty());
//  ASSERT_TRUE(state1.IsVelocityEmpty());
//  ASSERT_TRUE(!state2.IsEmpty());
//  ASSERT_TRUE(state2.IsVelocityEmpty());
//  ASSERT_TRUE(!state3.IsEmpty());
//  ASSERT_TRUE(state3.IsVelocityEmpty());
//
//  ASSERT_TRUE(!state4.IsEmpty());
//  ASSERT_TRUE(state4.IsPoseEmpty());
//  ASSERT_TRUE(!state5.IsEmpty());
//  ASSERT_TRUE(state5.IsPoseEmpty());
//  ASSERT_TRUE(!state6.IsEmpty());
//  ASSERT_TRUE(state6.IsPoseEmpty());
//
//  ASSERT_TRUE(state7.IsEmpty());
//
//  // Accessors to the empty component (velocity) must throw errors.
//  ASSERT_THROW(state1.get_velocity_vector(), std::logic_error);
//  ASSERT_THROW(state1.get_velocity()(0), std::logic_error);
//  ASSERT_THROW(state1.set_velocity_vector(VectorXd::Zero(0)),
//  std::logic_error);
//  // The state vectors must be accessible.
//  ASSERT_TRUE(state1.get_state_vector().isApprox(VectorXd::Zero(3)));
//
//  ASSERT_THROW(state2.get_velocity_vector(), std::logic_error);
//  ASSERT_THROW(state2.get_velocity()(0), std::logic_error);
//  ASSERT_THROW(state2.set_velocity_vector(VectorXd::Zero(0)),
//  std::logic_error);
//  ASSERT_TRUE(state2.get_state_vector().isApprox(VectorXd::Zero(4)));
//
//  ASSERT_THROW(state3.get_velocity_vector(), std::logic_error);
//  ASSERT_THROW(state3.get_velocity()(0), std::logic_error);
//  ASSERT_THROW(state3.set_velocity_vector(VectorXd::Zero(0)),
//  std::logic_error);
//  ASSERT_TRUE(state3.get_state_vector().isApprox(VectorXd::Zero(5)));
//
//  ASSERT_THROW(state7.get_velocity_vector(), std::logic_error);
//  ASSERT_THROW(state7.get_velocity()(0), std::logic_error);
//  ASSERT_THROW(state7.set_velocity_vector(VectorXd::Zero(0)),
//  std::logic_error);
//
//  // Setting the state vector should work for a partial state.
//  VectorXd v = VectorXd::Random(3);
//  state1.set_state_vector(v);
//  ASSERT_TRUE(state1.get_pose_vector().isApprox(v));
//  ASSERT_TRUE(state1.get_state_vector().isApprox(v));
//  // Resetting the value.
//  state1.set_state_vector(VectorXd::Zero(3));
//
//  // Accessors to the empty component (pose) must throw errors.
//  ASSERT_THROW(state4.get_pose_vector(), std::logic_error);
//  ASSERT_THROW(state4.get_pose()(0), std::logic_error);
//  ASSERT_THROW(state4.set_pose_vector(VectorXd::Zero(0)), std::logic_error);
//  ASSERT_TRUE(state4.get_state_vector().isApprox(VectorXd::Zero(3)));
//
//  ASSERT_THROW(state5.get_pose_vector(), std::logic_error);
//  ASSERT_THROW(state5.get_pose()(0), std::logic_error);
//  ASSERT_THROW(state5.set_pose_vector(VectorXd::Zero(0)), std::logic_error);
//  ASSERT_TRUE(state5.get_state_vector().isApprox(VectorXd::Zero(4)));
//
//  ASSERT_THROW(state6.get_pose_vector(), std::logic_error);
//  ASSERT_THROW(state6.get_pose()(0), std::logic_error);
//  ASSERT_THROW(state6.set_pose_vector(VectorXd::Zero(0)), std::logic_error);
//  ASSERT_TRUE(state6.get_state_vector().isApprox(VectorXd::Zero(5)));
//
//  ASSERT_THROW(state7.get_pose_vector(), std::logic_error);
//  ASSERT_THROW(state7.get_pose()(0), std::logic_error);
//  ASSERT_THROW(state7.set_pose_vector(VectorXd::Zero(0)), std::logic_error);
//
//  // Setting the state vector should work for a partial state.
//  v = VectorXd::Random(3);
//  state4.set_state_vector(v);
//  ASSERT_TRUE(state4.get_velocity_vector().isApprox(v));
//  ASSERT_TRUE(state4.get_state_vector().isApprox(v));
//  // Resetting the value.
//  state4.set_state_vector(VectorXd::Zero(3));
//
//  ASSERT_THROW(state7.get_state_vector(), std::logic_error);
//
//  // Operations should work as usual taking only the pose/velocity into
//  account.
//  State state_add_pose = state1 + State{VectorXd::Ones(3), VectorXd::Zero(0)};
//  State state_add_vel = state4 + State{VectorXd::Zero(0), VectorXd::Ones(3)};
//  ASSERT_TRUE(!state_add_pose.IsEmpty());
//  ASSERT_TRUE(state_add_pose.IsVelocityEmpty());
//  ASSERT_TRUE(!state_add_vel.IsEmpty());
//  ASSERT_TRUE(state_add_vel.IsPoseEmpty());
//  ASSERT_TRUE(state_add_pose.get_pose_vector().isApprox(VectorXd::Ones(3)));
//  ASSERT_TRUE(state_add_vel.get_velocity_vector().isApprox(VectorXd::Ones(3)));
//
//  State state_sub_pose = state2 - State{VectorXd::Ones(4), VectorXd::Zero(0)};
//  State state_sub_vel = state5 - State{VectorXd::Zero(0), VectorXd::Ones(4)};
//  ASSERT_TRUE(!state_sub_pose.IsEmpty());
//  ASSERT_TRUE(state_sub_pose.IsVelocityEmpty());
//  ASSERT_TRUE(!state_sub_vel.IsEmpty());
//  ASSERT_TRUE(state_sub_vel.IsPoseEmpty());
//  ASSERT_TRUE(
//      state_sub_pose.get_pose_vector().isApprox(-1 * VectorXd::Ones(4)));
//  ASSERT_TRUE(
//      state_sub_vel.get_velocity_vector().isApprox(-1 * VectorXd::Ones(4)));
//
//  State state_mult_pose = state3 * 5.;
//  State state_mult_vel = state6 * 5.;
//  ASSERT_TRUE(!state_mult_pose.IsEmpty());
//  ASSERT_TRUE(state_mult_pose.IsVelocityEmpty());
//  ASSERT_TRUE(!state_mult_vel.IsEmpty());
//  ASSERT_TRUE(state_mult_vel.IsPoseEmpty());
//  ASSERT_TRUE(state_mult_pose.get_pose_vector().isApprox(VectorXd::Zero(5)));
//  ASSERT_TRUE(state_mult_vel.get_velocity_vector().isApprox(VectorXd::Zero(5)));
//
//  State state_empty = state7 + State{};
//  ASSERT_TRUE(state_empty.IsEmpty());
//}
//
// TEST_F(StateTest, CreateLike) {
//  State state1 = State::CreateLike(state1_);
//  State state2 = State::CreateLike(state2_);
//
//  ASSERT_EQ(state1.get_size_pose(), 3);
//  ASSERT_EQ(state1.get_size_velocity(), 2);
//  ASSERT_TRUE(state1.get_pose_vector().isApprox(VectorXd::Zero(3)));
//  ASSERT_TRUE(state1.get_velocity_vector().isApprox(VectorXd::Zero(2)));
//
//  ASSERT_EQ(state2.get_size_pose(), 4);
//  ASSERT_EQ(state2.get_size_velocity(), 2);
//  ASSERT_TRUE(state2.get_pose_vector().isApprox(VectorXd::Zero(4)));
//  ASSERT_TRUE(state2.get_velocity_vector().isApprox(VectorXd::Zero(2)));
//}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

