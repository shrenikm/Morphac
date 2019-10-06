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

  // Copy constructor
  Pose pose4_ = pose3_;
};

TEST_F(PoseTest, DefaultObject) {
  ASSERT_EQ(pose1_.get_size(), pose2_.get_size());
  ASSERT_EQ(pose1_.get_pose(), pose2_.get_pose());
}

TEST_F(PoseTest, CopyConstructor) {
  ASSERT_EQ(pose3_.get_size(), pose4_.get_size());
  for (int i = 0; i < pose3_.get_size(); ++i) {
    ASSERT_EQ(pose3_.get_pose(i), pose4_.get_pose(i));
  }
}

TEST_F(PoseTest, SetPose) {
  pose3_.set_pose(1, 7.0);
  ASSERT_EQ(pose3_.get_pose(1), 7.0);
}

TEST_F(PoseTest, InvalidConstruction) {
  ASSERT_THROW(Pose(0), std::invalid_argument);
  ASSERT_THROW(Pose(VectorXd::Random(0)), std::invalid_argument);
}

TEST_F(PoseTest, InvalidGet) {
  ASSERT_THROW(pose1_.get_pose(-1), std::out_of_range);
  ASSERT_THROW(pose1_.get_pose(3), std::out_of_range);
}

TEST_F(PoseTest, InvalidSet) {
  ASSERT_THROW(pose1_.set_pose(-1, 1), std::out_of_range);
  ASSERT_THROW(pose1_.set_pose(7, 1), std::out_of_range);
  ASSERT_THROW(pose1_.set_pose(VectorXd::Random(0)), std::invalid_argument);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
