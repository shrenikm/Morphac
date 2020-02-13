#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/pose.h"

namespace {

using Eigen::VectorXd;

using morphac::constructs::Pose;

class PoseTest : public ::testing::Test {
 protected:
  PoseTest() {}

  void SetUp() override {}

  Pose pose1_{Pose(3)};
  Pose pose2_{Pose(VectorXd::Zero(3))};
  VectorXd rand_pose_ = VectorXd::Random(6);
  Pose pose3_{Pose(rand_pose_)};
  Pose pose4_ = pose3_;
};

TEST_F(PoseTest, Sizes) {
  ASSERT_EQ(pose1_.get_size(), pose2_.get_size());
  ASSERT_EQ(pose1_.get_pose_vector(), pose2_.get_pose_vector());
}

TEST_F(PoseTest, CopyConstructor) {
  ASSERT_EQ(pose3_.get_size(), pose4_.get_size());
  for (int i = 0; i < pose3_.get_size(); ++i) {
    ASSERT_EQ(pose3_.get_pose_at(i), pose4_.get_pose_at(i));
  }
}

TEST_F(PoseTest, SetPose) {
  pose3_.set_pose_at(1, 7.0);
  ASSERT_EQ(pose3_.get_pose_at(1), 7.0);
}

TEST_F(PoseTest, InvalidConstruction) {
  ASSERT_THROW(Pose(0), std::invalid_argument);
  ASSERT_THROW(Pose(VectorXd::Random(0)), std::invalid_argument);
}

TEST_F(PoseTest, InvalidGet) {
  ASSERT_THROW(pose1_.get_pose_at(-1), std::out_of_range);
  ASSERT_THROW(pose1_.get_pose_at(3), std::out_of_range);
}

TEST_F(PoseTest, InvalidSet) {
  ASSERT_THROW(pose1_.set_pose_vector(VectorXd::Random(4)),
               std::invalid_argument);
  ASSERT_THROW(pose1_.set_pose_vector(VectorXd::Random(2)),
               std::invalid_argument);
  ASSERT_THROW(pose1_.set_pose_at(-1, 1), std::out_of_range);
  ASSERT_THROW(pose1_.set_pose_at(7, 1), std::out_of_range);
}

TEST_F(PoseTest, Addition) {
  VectorXd v1(3), v2(3), q1(3), q2(3);
  v1 << 1, 2, 3;
  v2 << 4, 5, 6;
  q1 << 5, 7, 9;
  q2 << 9, 12, 15;

  Pose pose1(v1);
  Pose pose2(v2);
  pose1 += pose2;
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(q1));

  Pose pose3 = pose1 + pose2;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(q2));

  Pose pose4 = pose2 + pose1;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(pose4.get_pose_vector()));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
