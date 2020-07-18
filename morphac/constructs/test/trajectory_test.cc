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

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

