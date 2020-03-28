#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/pose.h"

namespace {

using std::ostringstream;
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
  Pose pose4_{pose3_};
};

TEST_F(PoseTest, Sizes) {
  ASSERT_EQ(pose1_.get_size(), pose2_.get_size());
  ASSERT_EQ(pose1_.get_pose_vector(), pose2_.get_pose_vector());
  ASSERT_EQ(pose3_.get_size(), 6);
}

TEST_F(PoseTest, CopyConstructor) {
  ASSERT_EQ(pose3_.get_size(), pose4_.get_size());
  ASSERT_TRUE(pose3_.get_pose_vector().isApprox(pose4_.get_pose_vector()));
}

TEST_F(PoseTest, GetPose) {
  ASSERT_TRUE(pose1_.get_pose_vector().isApprox(VectorXd::Zero(3)));

  for (int i = 0; i < pose2_.get_size(); ++i) {
    ASSERT_EQ(pose2_(i), 0);
  }
}

TEST_F(PoseTest, SetPose) {
  pose1_.set_pose_vector(VectorXd::Ones(3));
  ASSERT_TRUE(pose1_.get_pose_vector().isApprox(VectorXd::Ones(3)));

  VectorXd v = VectorXd::Random(pose3_.get_size());
  for (int i = 0; i < pose3_.get_size(); ++i) {
    pose3_(i) = v(i);
  }
  ASSERT_TRUE(pose3_.get_pose_vector().isApprox(v));
}

TEST_F(PoseTest, ConstPose) {
  const Pose pose{3};

  // For a const Pose, the values can only be accessed but not set, as a
  // reference (lvalue) is not returned for this overload of the operator.
  ASSERT_EQ(pose(0), 0);
}

TEST_F(PoseTest, InvalidConstruction) {
  ASSERT_THROW(Pose{-1}, std::invalid_argument);
}

TEST_F(PoseTest, EmptyConstruction) {
  Pose pose;

  // Assert emptiness.
  ASSERT_TRUE(pose.IsEmpty());

  // Accessors are invalid for empty Pose
  ASSERT_THROW(pose.get_pose_vector(), std::logic_error);
  ASSERT_THROW(pose(0), std::logic_error);
  ASSERT_THROW(pose.set_pose_vector(VectorXd::Random(0)), std::logic_error);
}

TEST_F(PoseTest, InvalidGet) {
  ASSERT_THROW(pose1_(-1), std::out_of_range);
  ASSERT_THROW(pose1_(3), std::out_of_range);
}

TEST_F(PoseTest, InvalidSet) {
  ASSERT_THROW(pose1_.set_pose_vector(VectorXd::Random(4)),
               std::invalid_argument);
  ASSERT_THROW(pose1_.set_pose_vector(VectorXd::Random(2)),
               std::invalid_argument);
}

TEST_F(PoseTest, Addition) {
  VectorXd p1(3), p2(3), d1(3), d2(3);
  p1 << 1, 2, 3;
  p2 << 4, 5, 6;
  d1 << 5, 7, 9;
  d2 << 9, 12, 15;

  Pose pose1{p1};
  Pose pose2{p2};
  pose1 += pose2;
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(d1));

  Pose pose3 = pose1 + pose2;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(d2));

  Pose pose4 = pose2 + pose1;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(pose4.get_pose_vector()));
}

TEST_F(PoseTest, Subtraction) {
  VectorXd p1(3), p2(3), d1(3), d2(3);
  p1 << 1, 2, 3;
  p2 << 4, 5, 6;
  d1 << -3, -3, -3;
  d2 << -7, -8, -9;

  Pose pose1{p1};
  Pose pose2{p2};
  pose1 -= pose2;
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(d1));

  Pose pose3 = pose1 - pose2;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(d2));

  Pose pose4 = pose2 - pose1;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(-1 * pose4.get_pose_vector()));
}

TEST_F(PoseTest, Multiplication) {
  VectorXd p1(3), p2(3), d1(3), d2(3);
  p1 << 1, 2, 3;
  p2 << 4, 5, 6;
  d1 << 2, 4, 6;
  d2 << -4, -5, -6;

  Pose pose1{p1};
  Pose pose2{p2};

  pose1 *= 2.0;
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(d1));

  Pose pose3 = pose2 * -1.0;
  Pose pose4 = -1 * pose2;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(d2));
  ASSERT_TRUE(pose4.get_pose_vector().isApprox(d2));
}

TEST_F(PoseTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << pose1_;

  // Multiple pose object representations in the stream.
  os << " " << pose3_ << std::endl;
}

TEST_F(PoseTest, EmptyPoseOperations) {
  // Basic operations on empty velocities must result in empty velocities.
  Pose pose1, pose2;

  Pose pose_add = pose1 + pose2;
  ASSERT_TRUE(pose_add.IsEmpty());

  Pose pose_sub = pose1 - pose2;
  ASSERT_TRUE(pose_sub.IsEmpty());

  Pose pose_mult = pose1 * 7.0;
  ASSERT_TRUE(pose_mult.IsEmpty());
}

TEST_F(PoseTest, CreateLike) {
  Pose pose1 = Pose::CreateLike(pose1_);
  Pose pose2 = Pose::CreateLike(pose3_);

  ASSERT_EQ(pose1.get_size(), 3);
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(VectorXd::Zero(3)));

  ASSERT_EQ(pose2.get_size(), 6);
  ASSERT_TRUE(pose2.get_pose_vector().isApprox(VectorXd::Zero(6)));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
