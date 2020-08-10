#include "gtest/gtest.h"

#include "constructs/include/coordinate.h"

namespace {

using std::ostringstream;

using morphac::constructs::Coordinate;
using Eigen::Matrix;
using Eigen::Vector2d;
using Eigen::VectorXd;

class CoordinateTest : public ::testing::Test {
 protected:
  CoordinateTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}

  Coordinate coord1_{2.0, 3.0};
  Coordinate coord2_{-1.5, 4.7};
  Coordinate coord3_{2.6, 2.1};
  Coordinate coord4_{3.1, 2.8};
  Coordinate coord5_{2.2, 5.9};
};

TEST_F(CoordinateTest, EigenConstruction) {
  VectorXd data(2);
  data << 2.0, 3.0;
  Coordinate coord1{data};

  ASSERT_EQ(coord1.get_x(), coord1_.get_x());
  ASSERT_EQ(coord1.get_y(), coord1_.get_y());
  ASSERT_TRUE(coord1.get_data().isApprox(coord1_.get_data()));
}

TEST_F(CoordinateTest, CopyConstructor) {
  Coordinate coord1(coord1_);

  ASSERT_EQ(coord1.get_x(), coord1_.get_x());
  ASSERT_EQ(coord1.get_y(), coord1_.get_y());
  ASSERT_TRUE(coord1.get_data().isApprox(coord1_.get_data()));
}

TEST_F(CoordinateTest, CopyAssignment) {
  Coordinate coord1 = coord1_;

  ASSERT_EQ(coord1.get_x(), coord1_.get_x());
  ASSERT_EQ(coord1.get_y(), coord1_.get_y());
  ASSERT_TRUE(coord1.get_data().isApprox(coord1_.get_data()));
}

TEST_F(CoordinateTest, DefaultCoordinate) {
  Coordinate default_coord;
  ASSERT_DOUBLE_EQ(default_coord.get_x(), 0.0);
  ASSERT_DOUBLE_EQ(default_coord.get_y(), 0.0);
  ASSERT_TRUE(default_coord.get_data().isApprox(Vector2d::Zero(2)));
}

TEST_F(CoordinateTest, ConstCoordinate) {
  // Make sure that read only operations work on const coordinates.
  const Coordinate coord{0., 0.};

  ASSERT_EQ(coord.get_x(), 0.);
  ASSERT_EQ(coord.get_y(), 0.);
  ASSERT_TRUE(coord.get_data().isApprox(Vector2d::Zero(2)));

  ASSERT_EQ(coord[0], 0.);
  ASSERT_EQ(coord[1], 0.);

  // We should be able to modify the data after const casting.
  const_cast<Coordinate &>(coord).set_data(Vector2d::Ones(2));

  ASSERT_EQ(coord.get_x(), 1.);
  ASSERT_EQ(coord.get_y(), 1.);
  ASSERT_TRUE(coord.get_data().isApprox(Vector2d::Ones(2)));
}

TEST_F(CoordinateTest, XCoordinates) {
  ASSERT_DOUBLE_EQ(coord1_.get_x(), 2.0);
  ASSERT_DOUBLE_EQ(coord2_.get_x(), -1.5);
  ASSERT_DOUBLE_EQ(coord3_.get_x(), 2.6);
  ASSERT_DOUBLE_EQ(coord4_.get_x(), 3.1);
  ASSERT_DOUBLE_EQ(coord5_.get_x(), 2.2);
}

TEST_F(CoordinateTest, YCoordinates) {
  ASSERT_DOUBLE_EQ(coord1_.get_y(), 3.0);
  ASSERT_DOUBLE_EQ(coord2_.get_y(), 4.7);
  ASSERT_DOUBLE_EQ(coord3_.get_y(), 2.1);
  ASSERT_DOUBLE_EQ(coord4_.get_y(), 2.8);
  ASSERT_DOUBLE_EQ(coord5_.get_y(), 5.9);
}

TEST_F(CoordinateTest, GetData) {
  VectorXd coord_data1(2), coord_data2(2), coord_data3(2), coord_data4(2),
      coord_data5(2);
  coord_data1 << 2, 3;
  coord_data2 << -1.5, 4.7;
  coord_data3 << 2.6, 2.1;
  coord_data4 << 3.1, 2.8;
  coord_data5 << 2.2, 5.9;

  ASSERT_TRUE(coord1_.get_data().isApprox(coord_data1));
  ASSERT_TRUE(coord2_.get_data().isApprox(coord_data2));
  ASSERT_TRUE(coord3_.get_data().isApprox(coord_data3));
  ASSERT_TRUE(coord4_.get_data().isApprox(coord_data4));
  ASSERT_TRUE(coord5_.get_data().isApprox(coord_data5));
}

TEST_F(CoordinateTest, SetData) {
  VectorXd coord_data1(2), coord_data2(2), coord_data3(2), coord_data4(2),
      coord_data5(2);
  coord_data1 << 5, 6;
  coord_data2 << 1., 0;
  coord_data3 << 6, -2.;
  coord_data4 << 3., 10;
  coord_data5 << -0.5, -0.5;

  coord1_.set_data(coord_data1);
  coord2_.set_data(coord_data2);
  coord3_.set_data(coord_data3);
  coord4_.set_data(coord_data4);
  coord5_.set_data(coord_data5);

  ASSERT_TRUE(coord1_.get_data().isApprox(coord_data1));
  ASSERT_TRUE(coord2_.get_data().isApprox(coord_data2));
  ASSERT_TRUE(coord3_.get_data().isApprox(coord_data3));
  ASSERT_TRUE(coord4_.get_data().isApprox(coord_data4));
  ASSERT_TRUE(coord5_.get_data().isApprox(coord_data5));
}

// TEST_F(CoordinateTest, Addition) {
//  Coordinate result = coord1_ + coord3_;
//
//  ASSERT_DOUBLE_EQ(result.get_x(), 0.5);
//  ASSERT_DOUBLE_EQ(result.get_y(), 7.7);
//
//  coord1_ += coord3_;
//
//  ASSERT_DOUBLE_EQ(coord1_.get_x(), 0.5);
//  ASSERT_DOUBLE_EQ(coord1_.get_y(), 7.7);
//}
//
// TEST_F(CoordinateTest, Subtraction) {
//  Coordinate result = coord1_ - coord3_;
//
//  ASSERT_DOUBLE_EQ(result.get_x(), 3.5);
//  ASSERT_DOUBLE_EQ(result.get_y(), -1.7);
//
//  coord1_ -= coord3_;
//
//  ASSERT_DOUBLE_EQ(coord1_.get_x(), 3.5);
//  ASSERT_DOUBLE_EQ(coord1_.get_y(), -1.7);
//}
//
// TEST_F(CoordinateTest, Multiplication) {
//  Coordinate result = 1.5 * coord3_;
//
//  ASSERT_DOUBLE_EQ(result.get_x(), -2.25);
//  ASSERT_DOUBLE_EQ(result.get_y(), 7.05);
//
//  coord3_ *= -2;
//  ASSERT_DOUBLE_EQ(coord3_.get_x(), 3.);
//  ASSERT_DOUBLE_EQ(coord3_.get_y(), -9.4);
//}
//
// TEST_F(CoordinateTest, GetAt) {
//  ASSERT_DOUBLE_EQ(coord3_[0], -1.5);
//  ASSERT_DOUBLE_EQ(coord3_[1], 4.7);
//}
//
// TEST_F(CoordinateTest, InvalidGetAt) {
//  ASSERT_THROW(coord3_[-1], std::out_of_range);
//  ASSERT_THROW(coord3_[2], std::out_of_range);
//}
//
// TEST_F(CoordinateTest, SetAt) {
//  coord1_[0] = 0;
//  coord1_[1] = 7;
//  coord3_[0] = -7;
//  coord3_[1] = 0;
//
//  ASSERT_EQ(coord1_[0], 0);
//  ASSERT_EQ(coord1_[1], 7);
//  ASSERT_EQ(coord3_[0], -7);
//  ASSERT_EQ(coord3_[1], 0);
//}
//
// TEST_F(CoordinateTest, StringRepresentation) {
//  // Testing that the << operator is overloaded properly.
//  // We don't test the actual string representation.
//  ostringstream os;
//  os << coord1_;
//
//  // Multiple Coordinate object representations in the stream.
//  os << " " << coord3_ << std::endl;
//}
//
// TEST_F(CoordinateTest, Equality) { ASSERT_TRUE(coord1_ == coord2_); }
//
// TEST_F(CoordinateTest, Inequality) {
//  ASSERT_TRUE(coord1_ != coord3_);
//  ASSERT_TRUE(coord1_ != coord4_);
//}
//
// TEST_F(CoordinateTest, Lesser) {
//  ASSERT_TRUE(zero_coord_ < coord1_);
//  ASSERT_TRUE(coord1_ < coord6_);
//  ASSERT_FALSE(coord1_ < coord2_);
//  ASSERT_FALSE(coord1_ < coord3_);
//}
//
// TEST_F(CoordinateTest, Greater) {
//  ASSERT_TRUE(coord1_ > coord3_);
//  ASSERT_FALSE(coord1_ > coord4_);
//  ASSERT_FALSE(coord1_ > coord2_);
//  ASSERT_FALSE(coord1_ > coord6_);
//}
//
// TEST_F(CoordinateTest, LesserEqual) {
//  ASSERT_TRUE(zero_coord_ <= coord1_);
//  ASSERT_TRUE(coord1_ <= coord6_);
//  ASSERT_TRUE(coord1_ <= coord2_);
//  ASSERT_FALSE(coord1_ <= coord3_);
//}
//
// TEST_F(CoordinateTest, GreaterEqual) {
//  ASSERT_TRUE(coord1_ >= coord3_);
//  ASSERT_FALSE(coord1_ >= coord4_);
//  ASSERT_TRUE(coord1_ >= coord2_);
//  ASSERT_FALSE(coord1_ >= coord6_);
//}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
