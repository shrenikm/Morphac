#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/state.h"

namespace {

using std::make_unique;
using std::move;
using std::unique_ptr;
using std::vector;

using Eigen::VectorXd;

using morphac::constructs::Pose;
using morphac::constructs::Velocity;
using morphac::constructs::State;

class StateTest : public ::testing::Test {
 protected:
  StateTest() {
    pose_vector1_.resize(4);
    velocity_vector1_.resize(2);
    state_vector1_.resize(6);
    pose_vector1_ << 1, 2, 4, 7.8;
    velocity_vector1_ << -4.5, -1.1;
    state_vector1_ << pose_vector1_, velocity_vector1_;
  }

  void SetUp() override {
    state1_ = new State{3, 2};
    state2_ = new State{pose_vector1_, velocity_vector1_};
    state3_ = new State{Pose(pose_vector1_), Velocity(velocity_vector1_)};
  }

  VectorXd pose_vector1_, velocity_vector1_;
  VectorXd state_vector1_;

  State *state1_, *state2_, *state3_;
};

TEST_F(StateTest, Sizes) {
  ASSERT_EQ(state1_->get_size_pose(), 3);
  ASSERT_EQ(state1_->get_size_velocity(), 2);
  ASSERT_EQ(state1_->get_size(), 5);

  ASSERT_EQ(state2_->get_size_pose(), 4);
  ASSERT_EQ(state2_->get_size_velocity(), 2);
  ASSERT_EQ(state2_->get_size(), 6);

  ASSERT_EQ(state3_->get_size_pose(), 4);
  ASSERT_EQ(state3_->get_size_velocity(), 2);
  ASSERT_EQ(state3_->get_size(), 6);
}

TEST_F(StateTest, GetPoseAndVelocity) {
  ASSERT_TRUE(state1_->get_pose_vector().isApprox(
      state1_->get_pose().get_pose_vector()));
  ASSERT_TRUE(state1_->get_velocity_vector().isApprox(
      state1_->get_velocity().get_velocity_vector()));

  ASSERT_TRUE(state2_->get_pose_vector().isApprox(
      state2_->get_pose().get_pose_vector()));
  ASSERT_TRUE(state2_->get_velocity_vector().isApprox(
      state2_->get_velocity().get_velocity_vector()));

  ASSERT_TRUE(state3_->get_pose_vector().isApprox(
      state3_->get_pose().get_pose_vector()));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(
      state3_->get_velocity().get_velocity_vector()));
}

TEST_F(StateTest, GetVector) {
  ASSERT_TRUE(state1_->get_pose_vector().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(state1_->get_velocity_vector().isApprox(VectorXd::Zero(2)));
  ASSERT_TRUE(state1_->get_state_vector().isApprox(VectorXd::Zero(5)));
  ASSERT_TRUE(state2_->get_pose_vector().isApprox(pose_vector1_));
  ASSERT_TRUE(state2_->get_velocity_vector().isApprox(velocity_vector1_));
  ASSERT_TRUE(state2_->get_state_vector().isApprox(state_vector1_));
  ASSERT_TRUE(state3_->get_pose_vector().isApprox(pose_vector1_));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(velocity_vector1_));
  ASSERT_TRUE(state3_->get_state_vector().isApprox(state_vector1_));
}

TEST_F(StateTest, GetAt) {
  for (int i = 0; i < pose_vector1_.size(); ++i) {
    ASSERT_EQ(state2_->get_pose()(i), pose_vector1_(i));
  }
  for (int i = 0; i < velocity_vector1_.size(); ++i) {
    ASSERT_EQ(state2_->get_velocity()(i), velocity_vector1_(i));
  }
  for (int i = 0; i < state_vector1_.size(); ++i) {
    ASSERT_EQ((*state2_)(i), state_vector1_(i));
  }
}

TEST_F(StateTest, SetVector) {
  VectorXd rand_pose = VectorXd::Random(4);
  VectorXd rand_velocity = VectorXd::Random(2);
  VectorXd rand_state = VectorXd::Random(6);

  state3_->set_pose_vector(rand_pose);
  state3_->set_velocity_vector(rand_velocity);
  ASSERT_TRUE(state3_->get_pose_vector().isApprox(rand_pose));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(rand_velocity));

  state3_->set_state_vector(rand_state);
  ASSERT_TRUE(state3_->get_pose_vector().isApprox(rand_state.head(4)));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(rand_state.tail(2)));
  ASSERT_TRUE(state3_->get_state_vector().isApprox(rand_state));
}

TEST_F(StateTest, SetAt) {
  VectorXd v = VectorXd::Random(state2_->get_size());

  for (int i = 0; i < state2_->get_size(); ++i) {
    (*state2_)(i) = v(i);
  }
  ASSERT_TRUE(state2_->get_state_vector().isApprox(v));
}

TEST_F(StateTest, ConstStateGet) {
  const State state{3, 3};

  // For a const State, the values can only be accessed but not set, as a
  // reference (lvalue) is not returned for this overload of the operator.
  ASSERT_EQ(state(0), 0);
}

TEST_F(StateTest, InvalidGet) {
  ASSERT_THROW(state2_->get_pose()(-1), std::out_of_range);
  ASSERT_THROW(state2_->get_pose()(4), std::out_of_range);
  ASSERT_THROW(state2_->get_velocity()(-1), std::out_of_range);
  ASSERT_THROW(state2_->get_velocity()(2), std::out_of_range);
  ASSERT_THROW((*state2_)(-1), std::out_of_range);
  ASSERT_THROW((*state2_)(6), std::out_of_range);
}

TEST_F(StateTest, InvalidSet) {
  // Invalid set at specific indices would be handled by the () operator getter
  // as the returned references is used to set as well.
  ASSERT_THROW(state2_->set_pose_vector(VectorXd::Random(3)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_pose_vector(VectorXd::Random(5)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_velocity_vector(VectorXd::Random(1)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_velocity_vector(VectorXd::Random(3)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_state_vector(VectorXd::Random(5)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_state_vector(VectorXd::Random(7)),
               std::invalid_argument);
}

TEST_F(StateTest, Addition) {
  VectorXd p1(3), p2(3), v1(2), v2(2);
  VectorXd d1(5), d2(5);
  VectorXd s1(5), s2(5);
  p1 << 1, 2, 3;
  p2 << 3, 2, 1;
  v1 << -1, 0;
  v2 << -2, 4;
  d1 << 4, 4, 4, -3, 4;
  d2 << 7, 6, 5, -5, 8;
  s1 << p1, v1;
  s2 << p2, v2;

  State state1{p1, v1};
  State state2{p2, v2};

  state1 += state2;
  ASSERT_TRUE(state1.get_state_vector().isApprox(d1));

  State state3 = state1 + state2;
  ASSERT_TRUE(state3.get_state_vector().isApprox(d2));

  State state4 = state2 + state1;
  ASSERT_TRUE(state3.get_state_vector().isApprox(state4.get_state_vector()));
}

TEST_F(StateTest, Subtraction) {
  VectorXd p1(3), p2(3), v1(2), v2(2);
  VectorXd d1(5), d2(5);
  VectorXd s1(5), s2(5);
  p1 << 1, 2, 3;
  p2 << 3, 2, 1;
  v1 << -1, 0;
  v2 << -2, 4;
  d1 << -2, 0, 2, 1, -4;
  d2 << -5, -2, 1, 3, -8;
  s1 << p1, v1;
  s2 << p2, v2;

  State state1{p1, v1};
  State state2{p2, v2};

  state1 -= state2;
  ASSERT_TRUE(state1.get_state_vector().isApprox(d1));

  State state3 = state1 - state2;
  ASSERT_TRUE(state3.get_state_vector().isApprox(d2));

  State state4 = state2 - state1;
  ASSERT_TRUE(
      state3.get_state_vector().isApprox(-1 * state4.get_state_vector()));
}

TEST_F(StateTest, Multiplication) {
  VectorXd p1(3), p2(3), v1(2), v2(2);
  VectorXd d1(5), d2(5);
  VectorXd s1(5), s2(5);
  p1 << 1, 2, 3;
  p2 << 3, 2, 1;
  v1 << -1, 0;
  v2 << -2, 4;
  d1 << 2, 4, 6, -2, 0;
  d2 << -3, -2, -1, 2, -4;

  State state1{p1, v1};
  State state2{p2, v2};

  state1 *= 2.0;
  ASSERT_TRUE(state1.get_state_vector().isApprox(d1));

  State state3 = state2 * -1.0;
  State state4 = -1 * state2;
  ASSERT_TRUE(state3.get_state_vector().isApprox(d2));
  ASSERT_TRUE(state4.get_state_vector().isApprox(d2));
}

TEST_F(StateTest, PartialConstruction) {
  // Constructing states without the velocity component.
  State state1{3, 0};
  State state2{VectorXd::Zero(4), VectorXd::Zero(0)};
  State state3{Pose(5), Velocity()};

  // Constructing states without the pose component.
  State state4{0, 3};
  State state5{VectorXd::Zero(0), VectorXd::Zero(4)};
  State state6{Pose(), Velocity(5)};

  // Both empty (empty state)
  State state7{0, 0};

  // Test emptiness.
  ASSERT_TRUE(!state1.is_empty());
  ASSERT_TRUE(state1.is_velocity_empty());
  ASSERT_TRUE(!state2.is_empty());
  ASSERT_TRUE(state2.is_velocity_empty());
  ASSERT_TRUE(!state3.is_empty());
  ASSERT_TRUE(state3.is_velocity_empty());

  ASSERT_TRUE(!state4.is_empty());
  ASSERT_TRUE(state4.is_pose_empty());
  ASSERT_TRUE(!state5.is_empty());
  ASSERT_TRUE(state5.is_pose_empty());
  ASSERT_TRUE(!state6.is_empty());
  ASSERT_TRUE(state6.is_pose_empty());

  ASSERT_TRUE(state7.is_empty());

  // Accessors to the empty component must throw errors.
  ASSERT_THROW(state1.get_velocity_vector(), std::logic_error);
  ASSERT_THROW(state1.get_velocity()(0), std::logic_error);
  ASSERT_THROW(state1.set_velocity_vector(VectorXd::Zero(0)), std::logic_error);
  ASSERT_THROW(state2.get_velocity_vector(), std::logic_error);
  ASSERT_THROW(state2.get_velocity()(0), std::logic_error);
  ASSERT_THROW(state2.set_velocity_vector(VectorXd::Zero(0)), std::logic_error);
  ASSERT_THROW(state3.get_velocity_vector(), std::logic_error);
  ASSERT_THROW(state3.get_velocity()(0), std::logic_error);
  ASSERT_THROW(state3.set_velocity_vector(VectorXd::Zero(0)), std::logic_error);
  ASSERT_THROW(state7.get_velocity_vector(), std::logic_error);
  ASSERT_THROW(state7.get_velocity()(0), std::logic_error);
  ASSERT_THROW(state7.set_velocity_vector(VectorXd::Zero(0)), std::logic_error);

  ASSERT_THROW(state4.get_pose_vector(), std::logic_error);
  ASSERT_THROW(state4.get_pose()(0), std::logic_error);
  ASSERT_THROW(state4.set_pose_vector(VectorXd::Zero(0)), std::logic_error);
  ASSERT_THROW(state5.get_pose_vector(), std::logic_error);
  ASSERT_THROW(state5.get_pose()(0), std::logic_error);
  ASSERT_THROW(state5.set_pose_vector(VectorXd::Zero(0)), std::logic_error);
  ASSERT_THROW(state6.get_pose_vector(), std::logic_error);
  ASSERT_THROW(state6.get_pose()(0), std::logic_error);
  ASSERT_THROW(state6.set_pose_vector(VectorXd::Zero(0)), std::logic_error);
  ASSERT_THROW(state7.get_pose_vector(), std::logic_error);
  ASSERT_THROW(state7.get_pose()(0), std::logic_error);
  ASSERT_THROW(state7.set_pose_vector(VectorXd::Zero(0)), std::logic_error);

  // Operations should work as usual taking only the pose/velocity into account.
  State state_add_pose = state1 + State{VectorXd::Ones(3), VectorXd::Zero(0)};
  State state_add_vel = state4 + State{VectorXd::Zero(0), VectorXd::Ones(3)};
  ASSERT_TRUE(!state_add_pose.is_empty());
  ASSERT_TRUE(state_add_pose.is_velocity_empty());
  ASSERT_TRUE(!state_add_vel.is_empty());
  ASSERT_TRUE(state_add_vel.is_pose_empty());
  ASSERT_TRUE(state_add_pose.get_pose_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(state_add_vel.get_velocity_vector().isApprox(VectorXd::Ones(3)));

  State state_sub_pose = state2 - State{VectorXd::Ones(4), VectorXd::Zero(0)};
  State state_sub_vel = state5 - State{VectorXd::Zero(0), VectorXd::Ones(4)};
  ASSERT_TRUE(!state_sub_pose.is_empty());
  ASSERT_TRUE(state_sub_pose.is_velocity_empty());
  ASSERT_TRUE(!state_sub_vel.is_empty());
  ASSERT_TRUE(state_sub_vel.is_pose_empty());
  ASSERT_TRUE(
      state_sub_pose.get_pose_vector().isApprox(-1 * VectorXd::Ones(4)));
  ASSERT_TRUE(
      state_sub_vel.get_velocity_vector().isApprox(-1 * VectorXd::Ones(4)));

  State state_mult_pose = state3 * 5.;
  State state_mult_vel = state6 * 5.;
  ASSERT_TRUE(!state_mult_pose.is_empty());
  ASSERT_TRUE(state_mult_pose.is_velocity_empty());
  ASSERT_TRUE(!state_mult_vel.is_empty());
  ASSERT_TRUE(state_mult_vel.is_pose_empty());
  ASSERT_TRUE(state_mult_pose.get_pose_vector().isApprox(VectorXd::Zero(5)));
  ASSERT_TRUE(state_mult_vel.get_velocity_vector().isApprox(VectorXd::Zero(5)));

  State state_empty = state7 + State{0, 0};
  ASSERT_TRUE(state_empty.is_empty());
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

