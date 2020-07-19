#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/trajectory.h"

namespace {

using std::make_unique;
using std::ostringstream;
using std::srand;
using std::unique_ptr;
using std::vector;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::constructs::State;
using morphac::constructs::Trajectory;

class TrajectoryTest : public ::testing::Test {
 protected:
  TrajectoryTest() {
    // set random seed for Eigen.
    srand(7);
    trajectory_data1_ = MatrixXd::Ones(10, 2);
    trajectory_data2_ = MatrixXd::Random(200, 6);
    knot_points_.push_back(State({1., 2.}, {0.}));
    knot_points_.push_back(State({-7., 0.}, {3.}));
    knot_points_.push_back(State({4., 6.}, {8.}));

    trajectory1_ = make_unique<Trajectory>(State(3, 2));
    trajectory2_ = make_unique<Trajectory>(knot_points_);
    trajectory3_ = make_unique<Trajectory>(trajectory_data1_, 2, 0);
    trajectory4_ = make_unique<Trajectory>(trajectory_data2_, 4, 2);
  }

  void SetUp() override {}

  MatrixXd trajectory_data1_, trajectory_data2_;
  vector<State> knot_points_;
  unique_ptr<Trajectory> trajectory1_, trajectory2_, trajectory3_, trajectory4_;
};

TEST_F(TrajectoryTest, CopyConstructor) {
  Trajectory trajectory1(*trajectory1_);
  Trajectory trajectory4(*trajectory4_);

  ASSERT_EQ(trajectory1.get_dim(), trajectory1_->get_dim());
  ASSERT_EQ(trajectory1.get_size(), trajectory1_->get_size());
  ASSERT_EQ(trajectory1.get_pose_size(), trajectory1_->get_pose_size());
  ASSERT_EQ(trajectory1.get_velocity_size(), trajectory1_->get_velocity_size());
  ASSERT_TRUE(trajectory1.get_data().isApprox(trajectory1_->get_data()));

  ASSERT_EQ(trajectory4.get_dim(), trajectory4_->get_dim());
  ASSERT_EQ(trajectory4.get_size(), trajectory4_->get_size());
  ASSERT_EQ(trajectory4.get_pose_size(), trajectory4_->get_pose_size());
  ASSERT_EQ(trajectory4.get_velocity_size(), trajectory4_->get_velocity_size());
  ASSERT_TRUE(trajectory4.get_data().isApprox(trajectory4_->get_data()));
}

TEST_F(TrajectoryTest, CopyAssignment) {
  Trajectory trajectory1 = *trajectory1_;
  Trajectory trajectory4 = *trajectory4_;

  // Making sure that the copied trajectories are equal.
  ASSERT_EQ(trajectory1.get_dim(), trajectory1_->get_dim());
  ASSERT_EQ(trajectory1.get_size(), trajectory1_->get_size());
  ASSERT_EQ(trajectory1.get_pose_size(), trajectory1_->get_pose_size());
  ASSERT_EQ(trajectory1.get_velocity_size(), trajectory1_->get_velocity_size());
  ASSERT_TRUE(trajectory1.get_data().isApprox(trajectory1_->get_data()));

  ASSERT_EQ(trajectory4.get_dim(), trajectory4_->get_dim());
  ASSERT_EQ(trajectory4.get_size(), trajectory4_->get_size());
  ASSERT_EQ(trajectory4.get_pose_size(), trajectory4_->get_pose_size());
  ASSERT_EQ(trajectory4.get_velocity_size(), trajectory4_->get_velocity_size());
  ASSERT_TRUE(trajectory4.get_data().isApprox(trajectory4_->get_data()));
}

TEST_F(TrajectoryTest, InvalidConstruction) {
  // The following ways of construction must throw an exception.
  // Constructing with an empty state.
  ASSERT_THROW(Trajectory trajectory{State(0, 0)}, std::invalid_argument);

  // Constructing with an empty knot points vector.
  vector<State> knot_points;
  ASSERT_THROW(Trajectory trajectory{knot_points}, std::invalid_argument);

  // Constructing with a vector of States that don't have the same sizes.
  knot_points.push_back(State(3, 4));
  knot_points.push_back(State(3, 4));
  knot_points.push_back(State(3, 3));
  ASSERT_THROW(Trajectory trajectory{knot_points}, std::invalid_argument);

  // Constructing with an empty matrix.
  ASSERT_THROW(Trajectory trajectory(MatrixXd::Zero(0, 0), 0, 0),
               std::invalid_argument);

  // Constructing with incorrect pose/velocity sizes.
  ASSERT_THROW(Trajectory trajectory(MatrixXd::Zero(20, 3), 3, 1),
               std::invalid_argument);
  ASSERT_THROW(Trajectory trajectory(MatrixXd::Zero(20, 3), 2, 0),
               std::invalid_argument);
}

TEST_F(TrajectoryTest, ConstTrajectory) {
  State state({1, 2}, {3, 4});
  const Trajectory trajectory{state};
  VectorXd data(4);
  data << 1, 2, 3, 4;

  // Get members.
  ASSERT_EQ(trajectory.get_dim(), 4);
  ASSERT_EQ(trajectory.get_size(), 1);
  ASSERT_EQ(trajectory.get_pose_size(), 2);
  ASSERT_EQ(trajectory.get_velocity_size(), 2);
  ASSERT_TRUE(trajectory.get_data().isApprox(data.transpose()));

  // Positional accessing.
  ASSERT_EQ(trajectory(0), state);

  // After const casting, we should be able to modify the data.
  MatrixXd new_data = MatrixXd::Random(100, 4);
  const_cast<Trajectory &>(trajectory).set_data(new_data);
  ASSERT_TRUE(trajectory.get_data().isApprox(new_data));
}

TEST_F(TrajectoryTest, GetDim) {
  ASSERT_EQ(trajectory1_->get_dim(), 5);
  ASSERT_EQ(trajectory2_->get_dim(), 3);
  ASSERT_EQ(trajectory3_->get_dim(), 2);
  ASSERT_EQ(trajectory4_->get_dim(), 6);
}

TEST_F(TrajectoryTest, GetSize) {
  ASSERT_EQ(trajectory1_->get_size(), 1);
  ASSERT_EQ(trajectory2_->get_size(), 3);
  ASSERT_EQ(trajectory3_->get_size(), 10);
  ASSERT_EQ(trajectory4_->get_size(), 200);
}

TEST_F(TrajectoryTest, GetPoseSize) {
  ASSERT_EQ(trajectory1_->get_pose_size(), 3);
  ASSERT_EQ(trajectory2_->get_pose_size(), 2);
  ASSERT_EQ(trajectory3_->get_pose_size(), 2);
  ASSERT_EQ(trajectory4_->get_pose_size(), 4);
}

TEST_F(TrajectoryTest, GetVelocitySize) {
  ASSERT_EQ(trajectory1_->get_velocity_size(), 2);
  ASSERT_EQ(trajectory2_->get_velocity_size(), 1);
  ASSERT_EQ(trajectory3_->get_velocity_size(), 0);
  ASSERT_EQ(trajectory4_->get_velocity_size(), 2);
}

TEST_F(TrajectoryTest, GetData) {
  MatrixXd trajectory2_data(3, 3);
  trajectory2_data << 1., 2., 0., -7., 0., 3., 4., 6., 8.;
  ASSERT_TRUE(trajectory1_->get_data().isApprox(MatrixXd::Zero(1, 5)));
  ASSERT_TRUE(trajectory2_->get_data().isApprox(trajectory2_data));
  ASSERT_TRUE(trajectory3_->get_data().isApprox(trajectory_data1_));
  ASSERT_TRUE(trajectory4_->get_data().isApprox(trajectory_data2_));
}

TEST_F(TrajectoryTest, SetData) {
  MatrixXd data1 = MatrixXd::Random(50, 5);
  MatrixXd data2 = MatrixXd::Random(500, 6);

  trajectory1_->set_data(data1);
  trajectory4_->set_data(data2);

  ASSERT_TRUE(trajectory1_->get_data().isApprox(data1));
  ASSERT_TRUE(trajectory4_->get_data().isApprox(data2));
}

TEST_F(TrajectoryTest, InvalidSetData) {
  // Making sure that if the data's number of columns do not equal dim, it
  // throws an exception.
  ASSERT_THROW(trajectory1_->set_data(MatrixXd::Random(1, 4)),
               std::invalid_argument);
  ASSERT_THROW(trajectory1_->set_data(MatrixXd::Random(10, 6)),
               std::invalid_argument);
  ASSERT_THROW(trajectory2_->set_data(MatrixXd::Random(3, 2)),
               std::invalid_argument);
  ASSERT_THROW(trajectory2_->set_data(MatrixXd::Random(10, 4)),
               std::invalid_argument);
  ASSERT_THROW(trajectory3_->set_data(MatrixXd::Random(10, 1)),
               std::invalid_argument);
  ASSERT_THROW(trajectory3_->set_data(MatrixXd::Random(20, 3)),
               std::invalid_argument);
  ASSERT_THROW(trajectory4_->set_data(MatrixXd::Random(200, 5)),
               std::invalid_argument);
  ASSERT_THROW(trajectory4_->set_data(MatrixXd::Random(20, 7)),
               std::invalid_argument);
}

TEST_F(TrajectoryTest, GetKnotPointAt) {
  // Tests the () overload.
  ASSERT_EQ((*trajectory1_)(0), State(3, 2));

  for (int i = 0; i < trajectory2_->get_size(); ++i) {
    ASSERT_EQ((*trajectory2_)(i), knot_points_.at(i));
  }

  for (int i = 0; i < trajectory3_->get_size(); ++i) {
    VectorXd pose_data =
        trajectory3_->get_data().row(i).head(trajectory3_->get_pose_size());
    VectorXd velocity_data =
        trajectory3_->get_data().row(i).tail(trajectory3_->get_velocity_size());
    ASSERT_EQ((*trajectory3_)(i), State(pose_data, velocity_data));
  }

  for (int i = 0; i < trajectory4_->get_size(); ++i) {
    VectorXd pose_data =
        trajectory4_->get_data().row(i).head(trajectory4_->get_pose_size());
    VectorXd velocity_data =
        trajectory4_->get_data().row(i).tail(trajectory4_->get_velocity_size());
    ASSERT_EQ((*trajectory4_)(i), State(pose_data, velocity_data));
  }
}

TEST_F(TrajectoryTest, GetKnotPointAtAfterSetData) {
  // Test that if the data is changed, the knot point State object retrieved
  // also reflects this change.
  MatrixXd data = MatrixXd::Random(75, 5);
  trajectory1_->set_data(data);

  for (int i = 0; i < data.rows(); ++i) {
    VectorXd pose_data =
        trajectory1_->get_data().row(i).head(trajectory1_->get_pose_size());
    VectorXd velocity_data =
        trajectory1_->get_data().row(i).tail(trajectory1_->get_velocity_size());
    ASSERT_EQ((*trajectory1_)(i), State(pose_data, velocity_data));
  }
}

TEST_F(TrajectoryTest, InvalidGetKnotPointAt) {
  // Calling the () overload with out of bounds indices must throw an exception.
  ASSERT_THROW((*trajectory1_)(-1), std::out_of_range);
  ASSERT_THROW((*trajectory1_)(1), std::out_of_range);
  ASSERT_THROW((*trajectory2_)(-1), std::out_of_range);
  ASSERT_THROW((*trajectory2_)(3), std::out_of_range);
  ASSERT_THROW((*trajectory3_)(-1), std::out_of_range);
  ASSERT_THROW((*trajectory3_)(10), std::out_of_range);
  ASSERT_THROW((*trajectory4_)(-1), std::out_of_range);
  ASSERT_THROW((*trajectory4_)(200), std::out_of_range);
}

TEST_F(TrajectoryTest, SetKnotPointAt) {
  // Test that the () overload can be used for setting.
  (*trajectory1_)(0) = State({1, 1, 1}, {1, 1});
  ASSERT_TRUE(trajectory1_->get_data().isApprox(MatrixXd::Ones(1, 5)));

  for (int i = 0; i < trajectory4_->get_size(); ++i) {
    (*trajectory4_)(i) = State({0, 0, 0, 0}, {0, 0});
  }
  ASSERT_TRUE(trajectory4_->get_data().isApprox(MatrixXd::Zero(200, 6)));
}

TEST_F(TrajectoryTest, Addition) {
  // Test the += operator.
  Trajectory trajectory1{*trajectory1_};

  trajectory1 += (*trajectory1_);

  ASSERT_EQ(trajectory1.get_dim(), 5);
  ASSERT_EQ(trajectory1.get_size(), 2);
  ASSERT_EQ(trajectory1.get_pose_size(), 3);
  ASSERT_EQ(trajectory1.get_velocity_size(), 2);
  ASSERT_TRUE(trajectory1.get_data().isApprox(MatrixXd::Zero(2, 5)));

  // Test adding with self.
  trajectory1 += trajectory1;

  ASSERT_EQ(trajectory1.get_dim(), 5);
  ASSERT_EQ(trajectory1.get_size(), 4);
  ASSERT_EQ(trajectory1.get_pose_size(), 3);
  ASSERT_EQ(trajectory1.get_velocity_size(), 2);
  ASSERT_TRUE(trajectory1.get_data().isApprox(MatrixXd::Zero(4, 5)));

  //// Test the + operator.
  MatrixXd end_trajectory_data = MatrixXd::Random(100, 6);
  MatrixXd trajectory_data(300, 6);
  trajectory_data << trajectory_data2_, end_trajectory_data;

  Trajectory end_trajectory{end_trajectory_data, 4, 2};

  Trajectory trajectory = (*trajectory4_) + end_trajectory;

  ASSERT_EQ(trajectory.get_dim(), 6);
  ASSERT_EQ(trajectory.get_size(), 300);
  ASSERT_EQ(trajectory.get_pose_size(), 4);
  ASSERT_EQ(trajectory.get_velocity_size(), 2);
  ASSERT_TRUE(trajectory.get_data().isApprox(trajectory_data));
}

TEST_F(TrajectoryTest, InvalidAddition) {
  // Addition is invalid if the trajectories don't have the same dimensions.
  ASSERT_THROW((*trajectory1_) += Trajectory(State(3, 3)),
               std::invalid_argument);
  ASSERT_THROW((*trajectory1_) += Trajectory(MatrixXd::Ones(10, 4), 2, 2),
               std::invalid_argument);

  // Addition is invalid if the trajectories don't have the same pose and
  // velocity sizes.
  ASSERT_THROW((*trajectory1_) += Trajectory(State(2, 2)),
               std::invalid_argument);
  ASSERT_THROW((*trajectory1_) += Trajectory(MatrixXd::Ones(10, 5), 2, 3),
               std::invalid_argument);

  ASSERT_THROW((*trajectory1_) += Trajectory(State(3, 3)),
               std::invalid_argument);
  ASSERT_THROW((*trajectory1_) += Trajectory(MatrixXd::Ones(10, 5), 2, 3),
               std::invalid_argument);
}

TEST_F(TrajectoryTest, Equality) {
  Trajectory trajectory1{MatrixXd::Zero(1, 5), 3, 2};
  Trajectory trajectory2{*trajectory2_};
  Trajectory trajectory3{trajectory_data1_, 2, 0};

  ASSERT_TRUE(trajectory1 == *trajectory1_);
  ASSERT_TRUE(trajectory2 == *trajectory2_);
  ASSERT_TRUE(trajectory3 == *trajectory3_);

  ASSERT_TRUE(trajectory1 != trajectory2);
  ASSERT_TRUE(trajectory2 != trajectory3);
  ASSERT_TRUE(trajectory3 != trajectory1);

  // Make sure that even if the dimensions are different, the trajectories
  // cannot be equal if they have different individual pose and velocity sizes.
  ASSERT_TRUE(trajectory1 != Trajectory(MatrixXd::Zero(1, 5), 2, 3));

  // Make sure that even if all the dimensions and sizes are equal, the
  // trajectories cannot be equal if they have different data.
  ASSERT_TRUE(trajectory1 != Trajectory(MatrixXd::Ones(1, 5), 3, 2));
}

TEST_F(TrajectoryTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << (*trajectory1_);

  // Multiple pose object representations in the stream.
  os << " " << (*trajectory2_) << std::endl;
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

