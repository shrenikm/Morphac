#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/pose.h"

namespace {

using std::initializer_list;
using std::make_unique;
using std::ostringstream;
using std::srand;
using std::unique_ptr;

using Eigen::VectorXd;

using morphac::constructs::Pose;

class PoseTest : public ::testing::Test {
 protected:
  PoseTest() {
    pose1_ = make_unique<Pose>(3);
    pose2_ = make_unique<Pose>(VectorXd::Zero(4));
    pose3_ = make_unique<Pose>(initializer_list<double>{0, 0, 0, 0, 0});
  }

  void SetUp() override {
    // Set random seed for Eigen.
    srand(7);
  }

  unique_ptr<Pose> pose1_, pose2_, pose3_;
};

TEST_F(PoseTest, CopyConstructor) {
  Pose pose1(*pose1_);

  VectorXd pose_vector = VectorXd::Random(4);
  Pose pose2(pose_vector);
  Pose pose3(pose2);

  ASSERT_TRUE(pose1.get_pose_vector().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(pose_vector));
}

TEST_F(PoseTest, InvalidConstruction) {
  ASSERT_THROW(Pose(-1), std::invalid_argument);
}

TEST_F(PoseTest, ConstPose) {
  // For a const Pose, the values can only be accessed but not set, as a
  // reference (lvalue) is not returned for this overload of the operator.

  const Pose pose(3);

  ASSERT_EQ(pose.get_size(), 3);
  ASSERT_TRUE(pose.get_pose_vector().isApprox(VectorXd::Zero(3)));

  // Making sure position accessing works.
  for (int i = 0; i < pose.get_size(); ++i) {
    ASSERT_EQ(pose(i), 0);
  }

  // After const casting, we should be able to modify the vector.
  const_cast<Pose &>(pose).set_pose_vector(VectorXd::Ones(3));
  ASSERT_TRUE(pose.get_pose_vector().isApprox(VectorXd::Ones(3)));
}

TEST_F(PoseTest, EmptyConstruction) {
  Pose pose(0);

  // Assert emptiness.
  ASSERT_TRUE(pose.IsEmpty());
  ASSERT_TRUE(Pose(VectorXd::Zero(0)).IsEmpty());
  ASSERT_TRUE(Pose{}.IsEmpty());

  // Accessors are invalid for empty Pose
  ASSERT_THROW(pose.get_pose_vector(), std::logic_error);
  ASSERT_THROW(pose(0), std::logic_error);
  ASSERT_THROW(pose.set_pose_vector(VectorXd::Random(0)), std::logic_error);
}

TEST_F(PoseTest, Sizes) {
  ASSERT_EQ(pose1_->get_size(), 3);
  ASSERT_EQ(pose2_->get_size(), 4);
  ASSERT_EQ(pose3_->get_size(), 5);

  // Empty Pose.
  ASSERT_EQ(Pose(0).get_size(), 0);
}

TEST_F(PoseTest, GetPoseVector) {
  ASSERT_TRUE(pose1_->get_pose_vector().isApprox(VectorXd::Zero(3)));
  ASSERT_TRUE(pose2_->get_pose_vector().isApprox(VectorXd::Zero(4)));
  ASSERT_TRUE(pose3_->get_pose_vector().isApprox(VectorXd::Zero(5)));

  VectorXd pose_vector = VectorXd::Random(6);
  Pose pose(pose_vector);

  ASSERT_TRUE(pose.get_pose_vector().isApprox(pose_vector));
}

TEST_F(PoseTest, GetPoseAt) {
  for (int i = 0; i < pose1_->get_size(); ++i) {
    ASSERT_EQ((*pose1_)(i), 0);
  }
  for (int i = 0; i < pose2_->get_size(); ++i) {
    ASSERT_EQ((*pose2_)(i), 0);
  }
  for (int i = 0; i < pose3_->get_size(); ++i) {
    ASSERT_EQ((*pose3_)(i), 0);
  }

  // Arbitrary Pose.
  VectorXd pose_vector = VectorXd::Random(7);
  Pose pose(pose_vector);

  for (int i = 0; i < pose.get_size(); ++i) {
    ASSERT_EQ(pose(i), pose_vector(i));
  }

  // Invalid get at.
  ASSERT_THROW((*pose1_)(-1), std::out_of_range);
  ASSERT_THROW((*pose1_)(3), std::out_of_range);

  ASSERT_THROW((*pose2_)(-1), std::out_of_range);
  ASSERT_THROW((*pose2_)(4), std::out_of_range);

  ASSERT_THROW((*pose2_)(-1), std::out_of_range);
  ASSERT_THROW((*pose2_)(5), std::out_of_range);
}

TEST_F(PoseTest, SetPoseVector) {
  VectorXd pose_vector = VectorXd::Random(4);
  VectorXd expected_vector(5);
  expected_vector << 1, 0, -1, 2.5, 0;

  pose1_->set_pose_vector(VectorXd::Ones(3));
  pose2_->set_pose_vector(pose_vector);
  pose3_->set_pose_vector({1, 0, -1, 2.5, 0});

  ASSERT_TRUE(pose1_->get_pose_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(pose2_->get_pose_vector().isApprox(pose_vector));
  ASSERT_TRUE(pose3_->get_pose_vector().isApprox(expected_vector));

  // Invalid set vector.
  ASSERT_THROW(pose1_->set_pose_vector(VectorXd::Ones(2)),
               std::invalid_argument);
  ASSERT_THROW(pose2_->set_pose_vector(VectorXd::Ones(5)),
               std::invalid_argument);
  ASSERT_THROW(pose3_->set_pose_vector({}), std::invalid_argument);
  ASSERT_THROW(pose3_->set_pose_vector({1, 2, 3, 4}), std::invalid_argument);
  ASSERT_THROW(pose3_->set_pose_vector({1, 2, 1, 2, 1, 2}),
               std::invalid_argument);
}

TEST_F(PoseTest, SetPoseAt) {
  for (int i = 0; i < pose1_->get_size(); ++i) {
    (*pose1_)(i) = 1;
  }
  for (int i = 0; i < pose2_->get_size(); ++i) {
    (*pose2_)(i) = 2;
  }
  for (int i = 0; i < pose3_->get_size(); ++i) {
    (*pose3_)(i) = -3.;
  }

  ASSERT_TRUE(pose1_->get_pose_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(pose2_->get_pose_vector().isApprox(2 * VectorXd::Ones(4)));
  ASSERT_TRUE(pose3_->get_pose_vector().isApprox(-3 * VectorXd::Ones(5)));

  // Invalid set at.
  ASSERT_THROW((*pose1_)(-1) = 0, std::out_of_range);
  ASSERT_THROW((*pose1_)(3) = 1, std::out_of_range);

  ASSERT_THROW((*pose2_)(-1) = 0, std::out_of_range);
  ASSERT_THROW((*pose2_)(4) = 1, std::out_of_range);

  ASSERT_THROW((*pose3_)(-1) = 0, std::out_of_range);
  ASSERT_THROW((*pose3_)(5) = 1, std::out_of_range);
}

TEST_F(PoseTest, Addition) {
  VectorXd p1(3), p2(3), d1(3), d2(3);
  p1 << 1, 2, 3;
  p2 << 4, -5, 6;
  d1 << 5, -3, 9;
  d2 << 9, -8, 15;

  Pose pose1{1, 2, 3};
  Pose pose2(p2);

  // Trivial addition.
  pose1 += Pose::CreateLike(pose1);
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(p1));

  pose1 = pose1 + Pose::CreateLike(pose1);
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(p1));

  pose1 += pose2;
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(d1));

  // Commutativity.
  Pose pose3 = pose1 + pose2;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(d2));

  Pose pose4 = pose2 + pose1;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(pose4.get_pose_vector()));

  // Empty addition.
  Pose empty_pose1(0), empty_pose2{};

  Pose empty_pose_add = empty_pose1 + empty_pose2;
  ASSERT_TRUE(empty_pose_add.IsEmpty());
}

TEST_F(PoseTest, Subtraction) {
  VectorXd p1(3), p2(3), d1(3), d2(3);
  p1 << 1, 2, 3;
  p2 << 4, -5, 6;
  d1 << -3, 7, -3;
  d2 << -7, 12, -9;

  Pose pose1({1, 2, 3});
  Pose pose2(p2);

  // Trivial subtraction.
  pose1 -= Pose::CreateLike(pose1);
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(p1));

  pose1 = pose1 - Pose::CreateLike(pose1);
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(p1));

  pose1 -= pose2;
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(d1));

  Pose pose3 = pose1 - pose2;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(d2));

  Pose pose4 = pose2 - pose1;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(-1 * pose4.get_pose_vector()));

  // Empty subtraction.
  Pose empty_pose1(0), empty_pose2{};

  Pose empty_pose_sub = empty_pose1 - empty_pose2;
  ASSERT_TRUE(empty_pose_sub.IsEmpty());
}

TEST_F(PoseTest, Multiplication) {
  VectorXd p1(3), p2(3), d1(3), d2(3);
  p1 << 1, 2, 3;
  p2 << 4, -5, 6;
  d1 << 2, 4, 6;
  d2 << -6, 7.5, -9;

  Pose pose1({1, 2, 3});
  Pose pose2(p2);

  // Trivial multiplication.
  pose1 = pose1 * 1.0;
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(p1));
  ASSERT_TRUE((0.0 * pose1).get_pose_vector().isApprox(VectorXd::Zero(3)));

  pose1 *= 2.0;
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(d1));

  // Commutativity.
  Pose pose3 = pose2 * -1.5;
  Pose pose4 = -1.5 * pose2;
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(d2));
  ASSERT_TRUE(pose4.get_pose_vector().isApprox(d2));

  // Empty multiplication.
  Pose empty_pose1(0), empty_pose2{};

  Pose empty_pose_mult1 = empty_pose1 * 7.0;
  Pose empty_pose_mult2 = empty_pose2 * 7.0;
  ASSERT_TRUE(empty_pose_mult1.IsEmpty());
  ASSERT_TRUE(empty_pose_mult2.IsEmpty());
}

TEST_F(PoseTest, Equality) {
  ASSERT_TRUE(Pose(3) == Pose(3));
  ASSERT_TRUE(Pose(3) == Pose(VectorXd::Zero(3)));
  ASSERT_TRUE(Pose(VectorXd::Ones(2)) == Pose({1, 1}));
  ASSERT_TRUE(Pose({1, 2}) == Pose({1, 2}));

  ASSERT_TRUE(Pose(3) != Pose(2));
  ASSERT_TRUE(Pose(3) != Pose(VectorXd::Zero(2)));
  ASSERT_TRUE(Pose(2) != Pose({0}));
  ASSERT_TRUE(Pose({1, 2}) != Pose({3, 4}));
  // Inequality for one digit more than the precision.
  ASSERT_TRUE(Pose({1, 2}) != Pose({1, 2.00001}));
}

TEST_F(PoseTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << (*pose1_);

  // Multiple pose object representations in the stream.
  os << " " << (*pose2_) << std::endl;
}

TEST_F(PoseTest, CreateLike) {
  Pose pose1 = Pose::CreateLike(*pose1_);
  Pose pose2 = Pose::CreateLike(*pose2_);
  Pose pose3 = Pose::CreateLike(*pose3_);

  ASSERT_EQ(pose1.get_size(), 3);
  ASSERT_TRUE(pose1.get_pose_vector().isApprox(VectorXd::Zero(3)));

  ASSERT_EQ(pose2.get_size(), 4);
  ASSERT_TRUE(pose2.get_pose_vector().isApprox(VectorXd::Zero(4)));

  ASSERT_EQ(pose3.get_size(), 5);
  ASSERT_TRUE(pose3.get_pose_vector().isApprox(VectorXd::Zero(5)));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
