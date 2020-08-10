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
  ASSERT_EQ(trajectory[0], state);

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
  ASSERT_EQ((*trajectory1_)[0], State(3, 2));

  for (int i = 0; i < trajectory2_->get_size(); ++i) {
    ASSERT_EQ((*trajectory2_)[i], knot_points_.at(i));
  }

  for (int i = 0; i < trajectory3_->get_size(); ++i) {
    VectorXd pose_data =
        trajectory3_->get_data().row(i).head(trajectory3_->get_pose_size());
    VectorXd velocity_data =
        trajectory3_->get_data().row(i).tail(trajectory3_->get_velocity_size());
    ASSERT_EQ((*trajectory3_)[i], State(pose_data, velocity_data));
  }

  for (int i = 0; i < trajectory4_->get_size(); ++i) {
    VectorXd pose_data =
        trajectory4_->get_data().row(i).head(trajectory4_->get_pose_size());
    VectorXd velocity_data =
        trajectory4_->get_data().row(i).tail(trajectory4_->get_velocity_size());
    ASSERT_EQ((*trajectory4_)[i], State(pose_data, velocity_data));
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
    ASSERT_EQ((*trajectory1_)[i], State(pose_data, velocity_data));
  }
}

TEST_F(TrajectoryTest, InvalidGetKnotPointAt) {
  // Calling the () overload with out of bounds indices must throw an exception.
  ASSERT_THROW((*trajectory1_)[-1], std::out_of_range);
  ASSERT_THROW((*trajectory1_)[1], std::out_of_range);
  ASSERT_THROW((*trajectory2_)[-1], std::out_of_range);
  ASSERT_THROW((*trajectory2_)[3], std::out_of_range);
  ASSERT_THROW((*trajectory3_)[-1], std::out_of_range);
  ASSERT_THROW((*trajectory3_)[10], std::out_of_range);
  ASSERT_THROW((*trajectory4_)[-1], std::out_of_range);
  ASSERT_THROW((*trajectory4_)[200], std::out_of_range);
}

TEST_F(TrajectoryTest, SetKnotPointAt) {
  // Test that the () overload can be used for setting.
  (*trajectory1_)[0] = State({1, 1, 1}, {1, 1});
  ASSERT_TRUE(trajectory1_->get_data().isApprox(MatrixXd::Ones(1, 5)));

  for (int i = 0; i < trajectory4_->get_size(); ++i) {
    (*trajectory4_)[i] = State({0, 0, 0, 0}, {0, 0});
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
}

TEST_F(TrajectoryTest, Inequality) {
  Trajectory trajectory1{MatrixXd::Zero(1, 5), 3, 2};
  Trajectory trajectory2{*trajectory2_};
  Trajectory trajectory3{trajectory_data1_, 2, 0};

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

TEST_F(TrajectoryTest, AddKnotPoint) {
  // Test that knot points can be added anywhere in the trajectory.
  trajectory1_->AddKnotPoint(State({1, 1, 1}, {1, 1}), 0);
  trajectory1_->AddKnotPoint(State({2, 2, 2}, {2, 2}), 1);
  trajectory1_->AddKnotPoint(State({3, 3, 3}, {3, 3}), 3);

  ASSERT_EQ(trajectory1_->get_size(), 4);
  ASSERT_EQ((*trajectory1_)[0], State({1, 1, 1}, {1, 1}));
  ASSERT_EQ((*trajectory1_)[1], State({2, 2, 2}, {2, 2}));
  ASSERT_EQ((*trajectory1_)[2], State({0, 0, 0}, {0, 0}));
  ASSERT_EQ((*trajectory1_)[3], State({3, 3, 3}, {3, 3}));

  // Testing on a trajectory with size > 1.
  // Add a point in the middle of the trajectory.
  trajectory4_->AddKnotPoint(State({1, 2, 3, 4}, {5, 6}), 99);

  // Test that the point has been added correctly.
  ASSERT_EQ(trajectory4_->get_size(), 201);
  ASSERT_EQ((*trajectory4_)[99], State({1, 2, 3, 4}, {5, 6}));
  // Making sure that the rest of the data has not been affected and is ordered
  // correctly.
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(0, 0, 99, 6)
                  .isApprox(trajectory_data2_.block(0, 0, 99, 6)));
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(100, 0, 101, 6)
                  .isApprox(trajectory_data2_.block(99, 0, 101, 6)));

  // Adding a knot point at the start of the trajectory.
  trajectory4_->AddKnotPoint(State(4, 2), 0);
  ASSERT_EQ(trajectory4_->get_size(), 202);
  ASSERT_EQ((*trajectory4_)[0], State({0, 0, 0, 0}, {0, 0}));
  ASSERT_EQ((*trajectory4_)[100], State({1, 2, 3, 4}, {5, 6}));
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(1, 0, 99, 6)
                  .isApprox(trajectory_data2_.block(0, 0, 99, 6)));
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(101, 0, 101, 6)
                  .isApprox(trajectory_data2_.block(99, 0, 101, 6)));

  // Adding a knot point at the end of the trajectory. We use the overload that
  // doesn't take in an index.
  trajectory4_->AddKnotPoint(State({1, 1, 1, 1}, {1, 1}));
  ASSERT_EQ(trajectory4_->get_size(), 203);
  ASSERT_EQ((*trajectory4_)[0], State({0, 0, 0, 0}, {0, 0}));
  ASSERT_EQ((*trajectory4_)[100], State({1, 2, 3, 4}, {5, 6}));
  ASSERT_EQ((*trajectory4_)[202], State({1, 1, 1, 1}, {1, 1}));
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(1, 0, 99, 6)
                  .isApprox(trajectory_data2_.block(0, 0, 99, 6)));
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(101, 0, 101, 6)
                  .isApprox(trajectory_data2_.block(99, 0, 101, 6)));
}

TEST_F(TrajectoryTest, InvalidAddKnotPoint) {
  // The function is invalid either if the state or the index is invalid.
  // Invalid state.
  ASSERT_THROW(trajectory1_->AddKnotPoint(State(3, 3)), std::invalid_argument);
  ASSERT_THROW(trajectory4_->AddKnotPoint(State(3, 2)), std::invalid_argument);

  // Invalid index.
  ASSERT_THROW(trajectory1_->AddKnotPoint(State(3, 2), -1), std::out_of_range);
  ASSERT_THROW(trajectory1_->AddKnotPoint(State(3, 2), 2), std::out_of_range);
  ASSERT_THROW(trajectory4_->AddKnotPoint(State(4, 2), -1), std::out_of_range);
  ASSERT_THROW(trajectory4_->AddKnotPoint(State(4, 2), 201), std::out_of_range);
}

TEST_F(TrajectoryTest, AddKnotPoints) {
  // Adding 4 knot points. One at the start, one at the end, and two other
  // between the existing points.
  // Making a few copies for testing.
  Trajectory trajectory2_copy1{*trajectory2_};
  Trajectory trajectory2_copy2{*trajectory2_};
  Trajectory trajectory2_copy3{*trajectory2_};

  State state1{{1., 1.}, {1.}};
  State state2{{2., 2.}, {2.}};
  State state3{{3., 3.}, {3.}};
  State state4{{4., 4.}, {4.}};
  vector<State> knot_points{state1, state2, state3, state4};
  vector<int> indices1{0, 2, 4, 6};
  vector<int> indices2{4, 2, 6, 0};
  vector<int> indices3{2, 6, 0, 4};

  trajectory2_copy1.AddKnotPoints(knot_points, indices1);

  // Making sure that the knot points are ordered correctly.
  ASSERT_EQ(trajectory2_copy1.get_size(), 7);
  ASSERT_EQ(trajectory2_copy1[0], state1);
  ASSERT_EQ(trajectory2_copy1[1], knot_points_.at(0));
  ASSERT_EQ(trajectory2_copy1[2], state2);
  ASSERT_EQ(trajectory2_copy1[3], knot_points_.at(1));
  ASSERT_EQ(trajectory2_copy1[4], state3);
  ASSERT_EQ(trajectory2_copy1[5], knot_points_.at(2));
  ASSERT_EQ(trajectory2_copy1[6], state4);

  // Making sure that we get the same result even if the indices are not
  // ordered.
  trajectory2_copy2.AddKnotPoints(knot_points, indices2);

  ASSERT_EQ(trajectory2_copy2.get_size(), 7);
  ASSERT_EQ(trajectory2_copy2[0], state1);
  ASSERT_EQ(trajectory2_copy2[1], knot_points_.at(0));
  ASSERT_EQ(trajectory2_copy2[2], state2);
  ASSERT_EQ(trajectory2_copy2[3], knot_points_.at(1));
  ASSERT_EQ(trajectory2_copy2[4], state3);
  ASSERT_EQ(trajectory2_copy2[5], knot_points_.at(2));
  ASSERT_EQ(trajectory2_copy2[6], state4);

  trajectory2_copy3.AddKnotPoints(knot_points, indices3);

  ASSERT_EQ(trajectory2_copy3.get_size(), 7);
  ASSERT_EQ(trajectory2_copy3[0], state1);
  ASSERT_EQ(trajectory2_copy3[1], knot_points_.at(0));
  ASSERT_EQ(trajectory2_copy3[2], state2);
  ASSERT_EQ(trajectory2_copy3[3], knot_points_.at(1));
  ASSERT_EQ(trajectory2_copy3[4], state3);
  ASSERT_EQ(trajectory2_copy3[5], knot_points_.at(2));
  ASSERT_EQ(trajectory2_copy3[6], state4);
}

TEST_F(TrajectoryTest, InvalidAddKnotPoints) {
  Trajectory trajectory2_copy1{*trajectory2_};
  Trajectory trajectory2_copy2{*trajectory2_};
  Trajectory trajectory2_copy3{*trajectory2_};
  Trajectory trajectory2_copy4{*trajectory2_};
  Trajectory trajectory2_copy5{*trajectory2_};

  State state1{{1., 1.}, {1.}};
  State state2{{2., 2.}, {2.}};
  State state3{{3., 3.}, {3.}};
  State state4{{4., 4.}, {4.}};
  vector<State> knot_points{state1, state2, state3, state4};
  vector<int> indices0{0, 2};
  vector<int> indices1{-1, 2, 4, 6};
  vector<int> indices2{6, 3, 7, 1};
  vector<int> indices3{3, 7, 6, -1};

  // Make sure that if the knot points and indices sizes don't match, it throws
  // an exception.
  ASSERT_THROW(trajectory2_copy1.AddKnotPoints(knot_points, indices0),
               std::invalid_argument);

  // Make sure that if the knot points sizes are invalid, it throws an
  // exception.
  ASSERT_THROW(trajectory2_copy2.AddKnotPoints(
                   vector<State>{State(2, 1), State(2, 2)}, indices0),
               std::invalid_argument);

  // Also make sure that even if there is any invalid index, it throws an
  // exception.
  ASSERT_THROW(trajectory2_copy3.AddKnotPoints(knot_points, indices1),
               std::out_of_range);
  ASSERT_THROW(trajectory2_copy4.AddKnotPoints(knot_points, indices2),
               std::out_of_range);
  ASSERT_THROW(trajectory2_copy5.AddKnotPoints(knot_points, indices3),
               std::out_of_range);
}

TEST_F(TrajectoryTest, RemoveKnotPoint) {
  trajectory1_->RemoveKnotPoint(0);

  ASSERT_EQ(trajectory1_->get_size(), 0);
  ASSERT_TRUE(trajectory1_->get_data().isApprox(MatrixXd::Zero(0, 5)));

  // Remove points from a trajectory with size > 1.
  trajectory4_->RemoveKnotPoint(0);
  ASSERT_EQ(trajectory4_->get_size(), 199);
  ASSERT_TRUE(
      trajectory4_->get_data().isApprox(trajectory_data2_.block(1, 0, 199, 6)));

  // Remove a point from the middle.
  trajectory4_->RemoveKnotPoint(99);
  ASSERT_EQ(trajectory4_->get_size(), 198);
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(0, 0, 99, 6)
                  .isApprox(trajectory_data2_.block(1, 0, 99, 6)));
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(99, 0, 99, 6)
                  .isApprox(trajectory_data2_.block(101, 0, 99, 6)));

  // Remove the last point. We use the overload that doesn't take an index.
  trajectory4_->RemoveKnotPoint();
  ASSERT_EQ(trajectory4_->get_size(), 197);
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(0, 0, 99, 6)
                  .isApprox(trajectory_data2_.block(1, 0, 99, 6)));
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(99, 0, 98, 6)
                  .isApprox(trajectory_data2_.block(101, 0, 98, 6)));
}

TEST_F(TrajectoryTest, InvalidRemoveKnotPoint) {
  // It should throw an exception if the index is invalid.
  ASSERT_THROW(trajectory1_->RemoveKnotPoint(-1), std::out_of_range);
  ASSERT_THROW(trajectory1_->RemoveKnotPoint(1), std::out_of_range);

  trajectory1_->RemoveKnotPoint(0);
  ASSERT_THROW(trajectory1_->RemoveKnotPoint(0), std::out_of_range);

  // Test for a trajectory with size > 1.
  ASSERT_THROW(trajectory4_->RemoveKnotPoint(-1), std::out_of_range);
  ASSERT_THROW(trajectory4_->RemoveKnotPoint(200), std::out_of_range);
}

TEST_F(TrajectoryTest, RemoveKnotPoints) {
  Trajectory trajectory2_copy1{*trajectory2_};
  Trajectory trajectory2_copy2{*trajectory2_};

  vector<int> indices1{2, 0};
  vector<int> indices2{0, 2};

  trajectory2_copy1.RemoveKnotPoints(indices1);
  ASSERT_EQ(trajectory2_copy1.get_size(), 1);
  ASSERT_EQ(trajectory2_copy1[0], knot_points_.at(1));

  // Making sure that it works even if the indices are not ordered.
  trajectory2_copy2.RemoveKnotPoints(indices2);
  ASSERT_EQ(trajectory2_copy2.get_size(), 1);
  ASSERT_EQ(trajectory2_copy2[0], knot_points_.at(1));

  // Testing the same on a bigger trajectory.
  trajectory4_->RemoveKnotPoints(vector<int>{0, 99, 199});
  ASSERT_EQ(trajectory4_->get_size(), 197);
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(0, 0, 98, 6)
                  .isApprox(trajectory_data2_.block(1, 0, 98, 6)));
  ASSERT_TRUE(trajectory4_->get_data()
                  .block(98, 0, 99, 6)
                  .isApprox(trajectory_data2_.block(100, 0, 99, 6)));
}

TEST_F(TrajectoryTest, InvalidRemoveKnotPoints) {
  Trajectory trajectory2_copy1{*trajectory2_};
  Trajectory trajectory2_copy2{*trajectory2_};

  Trajectory trajectory4_copy1{*trajectory4_};
  Trajectory trajectory4_copy2{*trajectory4_};

  ASSERT_THROW(trajectory2_copy1.RemoveKnotPoints(vector<int>{-1, 0}),
               std::out_of_range);
  ASSERT_THROW(trajectory2_copy2.RemoveKnotPoints(vector<int>{1, 3}),
               std::out_of_range);

  ASSERT_THROW(trajectory4_copy1.RemoveKnotPoints(vector<int>{-1, 0, 100}),
               std::out_of_range);
  ASSERT_THROW(trajectory4_copy2.RemoveKnotPoints(vector<int>{100, 200}),
               std::out_of_range);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

