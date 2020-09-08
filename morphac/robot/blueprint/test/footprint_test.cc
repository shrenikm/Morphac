#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "robot/blueprint/include/footprint.h"

namespace {

using Eigen::Array;
using Eigen::Dynamic;
using Eigen::Vector2d;

using morphac::common::aliases::Points;
using morphac::robot::blueprint::Footprint;

bool PointsInQuadrant(const Points& points, int quadrant) {
  // std::cout << points << std::endl;
  Array<double, Dynamic, 2> points_array = points.array();

  if (quadrant == 1) {
    // x and y need to be positive.
    return (points_array.col(0) >= 0).all() && (points_array.col(1) >= 0).all();
  } else if (quadrant == 2) {
    // x needs to be positive and y needs to be negative.
    return (points_array.col(0) >= 0).all() && (points_array.col(1) <= 0).all();
  } else if (quadrant == 3) {
    // x and y need to be negative.
    return (points_array.col(0) <= 0).all() && (points_array.col(1) <= 0).all();
  } else if (quadrant == 4) {
    // x needs to be negative and y needs to be positive.
    return (points_array.col(0) <= 0).all() && (points_array.col(1) >= 0).all();
  }
  MORPH_THROW(std::logic_error, "Invalid quadrant.");
}

class FootprintTest : public ::testing::Test {
 protected:
  FootprintTest() {
    // Set random seed for Eigen.
    srand(7);
    data_ = Points::Random(10, 2);
  }

  void SetUp() override {}

  Points data_;
};

TEST_F(FootprintTest, Construction) { Footprint footprint(data_); }

TEST_F(FootprintTest, CopyConstructor) {
  Footprint footprint1(data_);

  Footprint footprint2(footprint1);

  ASSERT_TRUE(footprint1.get_data().isApprox(footprint2.get_data()));
}

TEST_F(FootprintTest, CopyAssignment) {
  Footprint footprint1(data_);

  Footprint footprint2 = footprint1;

  ASSERT_TRUE(footprint1.get_data().isApprox(footprint2.get_data()));
}

TEST_F(FootprintTest, Accessors) {
  Footprint footprint(data_);
  ASSERT_TRUE(footprint.get_data().isApprox(data_));
}

TEST_F(FootprintTest, InvalidConstruction) {
  ASSERT_THROW(Footprint(Points::Zero(0, 2)), std::invalid_argument);
}

TEST_F(FootprintTest, CreateCircularFootprint) {
  // We don't need to test the values too much as geometry tests this
  // thoroughly. We just ensure that the relative center offsets the footprint
  // correctly.
  // Default center footprint
  auto footprint = Footprint::CreateCircularFootprint(2., 0.1);

  // Centering such that the points are all in a single quadrant.

  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateCircularFootprint(2., 0.1, Vector2d(-2., -2.))
          .get_data(),
      1));
  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateCircularFootprint(2., 0.1, Vector2d(-2., 2.)).get_data(),
      2));
  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateCircularFootprint(2., 0.1, Vector2d(2., 2.)).get_data(),
      3));
  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateCircularFootprint(2., 0.1, Vector2d(2., -2.)).get_data(),
      4));
}

TEST_F(FootprintTest, CreateRectangularFootprint) {
  // We don't need to test the values too much as geometry tests this
  // thoroughly. We just ensure that the relative center offsets the footprint
  // correctly.
  // Default center footprint
  auto footprint = Footprint::CreateRectangularFootprint(1., 1., 0.);

  // Centering such that the points are all in a single quadrant.

  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateRectangularFootprint(2., 2., 0., Vector2d(-1., -1.))
          .get_data(),
      1));
  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateRectangularFootprint(2., 2., 0., Vector2d(-1., 1.))
          .get_data(),
      2));
  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateRectangularFootprint(2., 2., 0., Vector2d(1., 1.))
          .get_data(),
      3));
  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateRectangularFootprint(2., 2., 0., Vector2d(1., -1.))
          .get_data(),
      4));
}

TEST_F(FootprintTest, CreateRoundedRectangularFootprint) {
  // We don't need to test the values too much as geometry tests this
  // thoroughly. We just ensure that the relative center offsets the footprint
  // correctly.
  // Default center footprint
  auto footprint =
      Footprint::CreateRoundedRectangularFootprint(1., 1., 0., 0.5, 0.1);

  // Centering such that the points are all in a single quadrant.

  ASSERT_TRUE(PointsInQuadrant(Footprint::CreateRoundedRectangularFootprint(
                                   2., 2., 0., 0.5, 0.1, Vector2d(-1., -1.))
                                   .get_data(),
                               1));
  ASSERT_TRUE(PointsInQuadrant(Footprint::CreateRoundedRectangularFootprint(
                                   2., 2., 0., 0.5, 0.1, Vector2d(-1., 1.))
                                   .get_data(),
                               2));
  ASSERT_TRUE(PointsInQuadrant(Footprint::CreateRoundedRectangularFootprint(
                                   2., 2., 0., 0.5, 0.1, Vector2d(1., 1.))
                                   .get_data(),
                               3));
  ASSERT_TRUE(PointsInQuadrant(Footprint::CreateRoundedRectangularFootprint(
                                   2., 2., 0., 0.5, 0.1, Vector2d(1., -1.))
                                   .get_data(),
                               4));
}

TEST_F(FootprintTest, CreateTriangularFootprint) {
  // We don't need to test the values too much as geometry tests this
  // thoroughly. We just ensure that the relative center offsets the footprint
  // correctly.
  // Default center footprint
  auto footprint = Footprint::CreateTriangularFootprint(2., 2., 0.);

  // Centering such that the points are all in a single quadrant.

  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateTriangularFootprint(2., 2., 0., Vector2d(-1., -1.))
          .get_data(),
      1));
  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateTriangularFootprint(2., 2., 0., Vector2d(-1., 1.))
          .get_data(),
      2));
  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateTriangularFootprint(2., 2., 0., Vector2d(1., 1.))
          .get_data(),
      3));
  ASSERT_TRUE(PointsInQuadrant(
      Footprint::CreateTriangularFootprint(2., 2., 0., Vector2d(1., -1.))
          .get_data(),
      4));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
