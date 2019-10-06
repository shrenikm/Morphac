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
  StateTest()
      : pose1_(make_unique<Pose>(VectorXd::Random(6))),
        velocity1_(make_unique<Velocity>(VectorXd::Random(5))) {
    pose_vector1_.resize(4);
    velocity_vector1_.resize(2);
    pose_vector1_ << 1, 2, 4, 7.8;
    velocity_vector1_ << -4.5, -1.1;
  }

  void SetUp() override {
    state1_ = new State(3, 2);
    state2_ = new State(pose_vector1_, velocity_vector1_);
    state3_ = new State(move(pose1_), move(velocity1_));
  }

  VectorXd pose_vector1_, velocity_vector1_;
  VectorXd pose_vector2_, velocity_vector2_;
  unique_ptr<Pose> pose1_;
  unique_ptr<Velocity> velocity1_;

  State *state1_, *state2_, *state3_;
};

TEST_F(StateTest, Sizes) {
  ASSERT_EQ(state1_->get_size_pose(), 3);
  ASSERT_EQ(state1_->get_size_velocity(), 2);
  ASSERT_EQ(state1_->get_size(), 5);
  ASSERT_EQ(state2_->get_size_pose(), 4);
  ASSERT_EQ(state2_->get_size_velocity(), 2);
  ASSERT_EQ(state2_->get_size(), 6);
  ASSERT_EQ(state3_->get_size_pose(), 6);
  ASSERT_EQ(state3_->get_size_velocity(), 5);
  ASSERT_EQ(state3_->get_size(), 11);
}

TEST_F(StateTest, GetVector) {
  ASSERT_TRUE(state1_->get_pose_vector().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(state1_->get_velocity_vector().isApprox(VectorXd::Zero(2)));
  ASSERT_TRUE(state2_->get_pose_vector().isApprox(pose_vector1_));
  ASSERT_TRUE(state2_->get_velocity_vector().isApprox(velocity_vector1_));
}

TEST_F(StateTest, GetPoseAndVelocity) {
  ASSERT_TRUE(
      state3_->get_pose_vector().isApprox(state3_->get_pose().get_pose()));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(
      state3_->get_velocity().get_velocity()));
}

TEST_F(StateTest, GetAt) {
  for (int i = 0; i < pose_vector1_.size(); ++i) {
    ASSERT_EQ(state2_->get_pose_at(i), pose_vector1_(i));
  }
  for (int i = 0; i < velocity_vector1_.size(); ++i) {
    ASSERT_EQ(state2_->get_velocity_at(i), velocity_vector1_(i));
  }
}

TEST_F(StateTest, InvalidGet) {
  ASSERT_THROW(state2_->get_pose_at(-1), std::out_of_range);
  ASSERT_THROW(state2_->get_pose_at(4), std::out_of_range);
  ASSERT_THROW(state2_->get_velocity_at(-1), std::out_of_range);
  ASSERT_THROW(state2_->get_velocity_at(2), std::out_of_range);
}

TEST_F(StateTest, SetVector) {
  VectorXd rand_pose = VectorXd::Random(6);
  VectorXd rand_velocity = VectorXd::Random(5);
  state3_->set_pose_vector(rand_pose);
  state3_->set_velocity_vector(rand_velocity);
  ASSERT_TRUE(state3_->get_pose_vector().isApprox(rand_pose));
  ASSERT_TRUE(state3_->get_velocity_vector().isApprox(rand_velocity));
}

TEST_F(StateTest, SetAt) {
  state2_->set_pose_at(1, 0.1);
  state2_->set_velocity_at(0, 4.5);
  VectorXd changed_pose = pose_vector1_;
  VectorXd changed_velocity = velocity_vector1_;
  changed_pose(1) = 0.1;
  changed_velocity(0) = 4.5;
  ASSERT_TRUE(state2_->get_pose_vector().isApprox(changed_pose));
  ASSERT_TRUE(state2_->get_velocity_vector().isApprox(changed_velocity));
}

TEST_F(StateTest, InvalidSet) {
  ASSERT_THROW(state2_->set_pose_vector(VectorXd::Random(3)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_pose_vector(VectorXd::Random(5)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_velocity_vector(VectorXd::Random(1)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_velocity_vector(VectorXd::Random(3)),
               std::invalid_argument);
  ASSERT_THROW(state2_->set_pose_at(-1, 0), std::out_of_range);
  ASSERT_THROW(state2_->set_pose_at(4, 0), std::out_of_range);
  ASSERT_THROW(state2_->set_velocity_at(-1, 0), std::out_of_range);
  ASSERT_THROW(state2_->set_velocity_at(2, 0), std::out_of_range);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

