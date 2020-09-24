#include "constructs/include/coordinate.h"

#include "gtest/gtest.h"

namespace {

using std::ostringstream;

using Eigen::Matrix;
using Eigen::VectorXd;

using morphac::common::aliases::Point;
using morphac::constructs::Coordinate;

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
  Coordinate coord4_{2.0, 4.0};
  Coordinate coord5_{2.6, -1.};
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
  ASSERT_TRUE(default_coord.get_data().isApprox(Point::Zero(2)));
}

TEST_F(CoordinateTest, ConstCoordinate) {
  // Make sure that read only operations work on const coordinates.
  const Coordinate coord{0., 0.};

  ASSERT_EQ(coord.get_x(), 0.);
  ASSERT_EQ(coord.get_y(), 0.);
  ASSERT_TRUE(coord.get_data().isApprox(Point::Zero(2)));

  ASSERT_EQ(coord[0], 0.);
  ASSERT_EQ(coord[1], 0.);

  // We should be able to modify the data after const casting.
  const_cast<Coordinate &>(coord).set_data(Point::Ones(2));

  ASSERT_EQ(coord.get_x(), 1.);
  ASSERT_EQ(coord.get_y(), 1.);
  ASSERT_TRUE(coord.get_data().isApprox(Point::Ones(2)));
}

TEST_F(CoordinateTest, XCoordinates) {
  ASSERT_DOUBLE_EQ(coord1_.get_x(), 2.0);
  ASSERT_DOUBLE_EQ(coord2_.get_x(), -1.5);
  ASSERT_DOUBLE_EQ(coord3_.get_x(), 2.6);
  ASSERT_DOUBLE_EQ(coord4_.get_x(), 2.0);
  ASSERT_DOUBLE_EQ(coord5_.get_x(), 2.6);
}

TEST_F(CoordinateTest, YCoordinates) {
  ASSERT_DOUBLE_EQ(coord1_.get_y(), 3.0);
  ASSERT_DOUBLE_EQ(coord2_.get_y(), 4.7);
  ASSERT_DOUBLE_EQ(coord3_.get_y(), 2.1);
  ASSERT_DOUBLE_EQ(coord4_.get_y(), 4.);
  ASSERT_DOUBLE_EQ(coord5_.get_y(), -1);
}

TEST_F(CoordinateTest, GetData) {
  VectorXd coord_data1(2), coord_data2(2), coord_data3(2), coord_data4(2),
      coord_data5(2);
  coord_data1 << 2, 3;
  coord_data2 << -1.5, 4.7;
  coord_data3 << 2.6, 2.1;
  coord_data4 << 2.0, 4.;
  coord_data5 << 2.6, -1;

  ASSERT_TRUE(coord1_.get_data().isApprox(coord_data1));
  ASSERT_TRUE(coord2_.get_data().isApprox(coord_data2));
  ASSERT_TRUE(coord3_.get_data().isApprox(coord_data3));
  ASSERT_TRUE(coord4_.get_data().isApprox(coord_data4));
  ASSERT_TRUE(coord5_.get_data().isApprox(coord_data5));
}

TEST_F(CoordinateTest, GetCoordinateAt) {
  ASSERT_DOUBLE_EQ(coord1_[0], 2.0);
  ASSERT_DOUBLE_EQ(coord1_[1], 3.0);
  ASSERT_DOUBLE_EQ(coord2_[0], -1.5);
  ASSERT_DOUBLE_EQ(coord2_[1], 4.7);

  // Invalid get at.

  ASSERT_THROW(coord1_[-1], std::out_of_range);
  ASSERT_THROW(coord1_[2], std::out_of_range);
  ASSERT_THROW(coord2_[-1], std::out_of_range);
  ASSERT_THROW(coord2_[2], std::out_of_range);
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

TEST_F(CoordinateTest, SetCoordinateAt) {
  coord1_[0] = 0;
  coord1_[1] = 7;
  coord2_[0] = -7;
  coord2_[1] = 0;

  ASSERT_EQ(coord1_[0], 0);
  ASSERT_EQ(coord1_[1], 7);
  ASSERT_EQ(coord2_[0], -7);
  ASSERT_EQ(coord2_[1], 0);

  // Invalid set at.
  ASSERT_THROW(coord1_[-1] = 0, std::out_of_range);
  ASSERT_THROW(coord1_[2] = 0, std::out_of_range);
  ASSERT_THROW(coord2_[-1] = 0, std::out_of_range);
  ASSERT_THROW(coord2_[2] = 0, std::out_of_range);
}

TEST_F(CoordinateTest, Addition) {
  Coordinate result = coord1_ + coord2_;

  ASSERT_DOUBLE_EQ(result.get_x(), 0.5);
  ASSERT_DOUBLE_EQ(result.get_y(), 7.7);

  coord1_ += coord2_;

  ASSERT_DOUBLE_EQ(coord1_.get_x(), 0.5);
  ASSERT_DOUBLE_EQ(coord1_.get_y(), 7.7);
}

TEST_F(CoordinateTest, Subtraction) {
  Coordinate result = coord1_ - coord2_;

  ASSERT_DOUBLE_EQ(result.get_x(), 3.5);
  ASSERT_DOUBLE_EQ(result.get_y(), -1.7);

  coord1_ -= coord2_;

  ASSERT_DOUBLE_EQ(coord1_.get_x(), 3.5);
  ASSERT_DOUBLE_EQ(coord1_.get_y(), -1.7);
}

TEST_F(CoordinateTest, Multiplication) {
  Coordinate result = 1.5 * coord3_;

  ASSERT_DOUBLE_EQ(result.get_x(), 3.9);
  ASSERT_DOUBLE_EQ(result.get_y(), 3.15);

  coord3_ *= -2;
  ASSERT_DOUBLE_EQ(coord3_.get_x(), -5.2);
  ASSERT_DOUBLE_EQ(coord3_.get_y(), -4.2);
}

TEST_F(CoordinateTest, Equality) {
  ASSERT_TRUE(coord1_ == Coordinate{coord1_});
  ASSERT_TRUE(coord2_ == Coordinate{coord2_});
  ASSERT_TRUE(coord3_ == Coordinate{coord3_});
  ASSERT_TRUE(coord4_ == Coordinate{coord4_});
  ASSERT_TRUE(coord5_ == Coordinate{coord5_});
}

TEST_F(CoordinateTest, Inequality) {
  ASSERT_TRUE(coord1_ != coord2_);
  ASSERT_TRUE(coord2_ != coord3_);
  ASSERT_TRUE(coord3_ != coord4_);
  ASSERT_TRUE(coord4_ != coord5_);
  ASSERT_TRUE(coord5_ != coord1_);
}

TEST_F(CoordinateTest, Lesser) {
  ASSERT_TRUE(coord1_ < coord3_);
  ASSERT_TRUE(coord1_ < coord4_);
  ASSERT_TRUE(coord1_ < coord5_);

  ASSERT_TRUE(coord2_ < coord1_);
  ASSERT_TRUE(coord2_ < coord3_);
  ASSERT_TRUE(coord2_ < coord4_);
  ASSERT_TRUE(coord2_ < coord5_);

  ASSERT_TRUE(coord4_ < coord3_);
  ASSERT_TRUE(coord4_ < coord5_);

  ASSERT_TRUE(coord5_ < coord3_);
}

TEST_F(CoordinateTest, Greater) {
  ASSERT_TRUE(coord1_ > coord2_);

  ASSERT_TRUE(coord3_ > coord1_);
  ASSERT_TRUE(coord3_ > coord2_);
  ASSERT_TRUE(coord3_ > coord4_);
  ASSERT_TRUE(coord3_ > coord5_);

  ASSERT_TRUE(coord4_ > coord1_);
  ASSERT_TRUE(coord4_ > coord2_);

  ASSERT_TRUE(coord5_ > coord1_);
  ASSERT_TRUE(coord5_ > coord2_);
  ASSERT_TRUE(coord5_ > coord4_);
}

TEST_F(CoordinateTest, LesserEqual) {
  // Test regular lesser.
  ASSERT_TRUE(coord1_ < coord3_);
  ASSERT_TRUE(coord1_ < coord4_);
  ASSERT_TRUE(coord1_ < coord5_);

  ASSERT_TRUE(coord2_ < coord1_);
  ASSERT_TRUE(coord2_ < coord3_);
  ASSERT_TRUE(coord2_ < coord4_);
  ASSERT_TRUE(coord2_ < coord5_);

  ASSERT_TRUE(coord4_ < coord3_);
  ASSERT_TRUE(coord4_ < coord5_);

  ASSERT_TRUE(coord5_ < coord3_);

  // Test equality.
  ASSERT_TRUE(coord1_ <= coord1_);
  ASSERT_TRUE(coord2_ <= coord2_);
  ASSERT_TRUE(coord3_ <= coord3_);
  ASSERT_TRUE(coord4_ <= coord4_);
  ASSERT_TRUE(coord5_ <= coord5_);
}

TEST_F(CoordinateTest, GreaterEqual) {
  // Test regular greater.
  ASSERT_TRUE(coord1_ > coord2_);

  ASSERT_TRUE(coord3_ > coord1_);
  ASSERT_TRUE(coord3_ > coord2_);
  ASSERT_TRUE(coord3_ > coord4_);
  ASSERT_TRUE(coord3_ > coord5_);

  ASSERT_TRUE(coord4_ > coord1_);
  ASSERT_TRUE(coord4_ > coord2_);

  ASSERT_TRUE(coord5_ > coord1_);
  ASSERT_TRUE(coord5_ > coord2_);
  ASSERT_TRUE(coord5_ > coord4_);

  // Test equality.
  ASSERT_TRUE(coord1_ >= coord1_);
  ASSERT_TRUE(coord2_ >= coord2_);
  ASSERT_TRUE(coord3_ >= coord3_);
  ASSERT_TRUE(coord4_ >= coord4_);
  ASSERT_TRUE(coord5_ >= coord5_);
}

TEST_F(CoordinateTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << coord1_;

  // Multiple Coordinate object representations in the stream.
  os << " " << coord2_ << std::endl;
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
