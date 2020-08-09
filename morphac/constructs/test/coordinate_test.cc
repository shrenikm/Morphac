#include "gtest/gtest.h"

#include "constructs/include/coordinate.h"

namespace {

using std::ostringstream;

using morphac::constructs::Coordinate;
using Eigen::Matrix;
using Eigen::VectorXd;

class CoordinateTest : public ::testing::Test {
 protected:
  CoordinateTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}

  Coordinate default_coord_{};
  Coordinate zero_coord_{1.0, 2.0};
  Coordinate coord1_{2.0, 3.0};
  // Copy constructor.
  Coordinate coord2_ = coord1_;
  Coordinate coord3_{-1.5, 4.7};
  Coordinate coord4_{2.6, 2.1};
  // Copy constructor.
  Coordinate coord5_{Coordinate(3.1, 2.8)};
  Coordinate coord6_{Coordinate(2.2, 5.9)};
};

TEST_F(CoordinateTest, DefaultObject) {
  ASSERT_DOUBLE_EQ(default_coord_.get_x(), 0.0);
  ASSERT_DOUBLE_EQ(default_coord_.get_y(), 0.0);
}

TEST_F(CoordinateTest, Initialization) {
  ASSERT_DOUBLE_EQ(zero_coord_.get_x(), 1.0);
  ASSERT_DOUBLE_EQ(zero_coord_.get_y(), 2.0);
}

TEST_F(CoordinateTest, GetData) {
  VectorXd coord_data = coord1_.get_data();
  ASSERT_EQ(coord_data.size(), 2);
  ASSERT_EQ(coord_data(0), 2.);
  ASSERT_EQ(coord_data(1), 3.);
}

TEST_F(CoordinateTest, SetData) {
  VectorXd coord_data(2);
  coord_data << -2, -3;
  coord1_.set_data(coord_data);

  ASSERT_EQ(coord1_.get_x(), -2);
  ASSERT_EQ(coord1_.get_y(), -3);
}

TEST_F(CoordinateTest, Addition) {
  Coordinate result = coord1_ + coord3_;

  ASSERT_DOUBLE_EQ(result.get_x(), 0.5);
  ASSERT_DOUBLE_EQ(result.get_y(), 7.7);

  coord1_ += coord3_;

  ASSERT_DOUBLE_EQ(coord1_.get_x(), 0.5);
  ASSERT_DOUBLE_EQ(coord1_.get_y(), 7.7);
}

TEST_F(CoordinateTest, Subtraction) {
  Coordinate result = coord1_ - coord3_;

  ASSERT_DOUBLE_EQ(result.get_x(), 3.5);
  ASSERT_DOUBLE_EQ(result.get_y(), -1.7);

  coord1_ -= coord3_;

  ASSERT_DOUBLE_EQ(coord1_.get_x(), 3.5);
  ASSERT_DOUBLE_EQ(coord1_.get_y(), -1.7);
}

TEST_F(CoordinateTest, Multiplication) {
  Coordinate result = 1.5 * coord3_;

  ASSERT_DOUBLE_EQ(result.get_x(), -2.25);
  ASSERT_DOUBLE_EQ(result.get_y(), 7.05);

  coord3_ *= -2;
  ASSERT_DOUBLE_EQ(coord3_.get_x(), 3.);
  ASSERT_DOUBLE_EQ(coord3_.get_y(), -9.4);
}

TEST_F(CoordinateTest, GetAt) {
  ASSERT_DOUBLE_EQ(coord3_[0], -1.5);
  ASSERT_DOUBLE_EQ(coord3_[1], 4.7);
}

TEST_F(CoordinateTest, InvalidGetAt) {
  ASSERT_THROW(coord3_[-1], std::out_of_range);
  ASSERT_THROW(coord3_[2], std::out_of_range);
}

TEST_F(CoordinateTest, SetAt) {
  coord1_[0] = 0;
  coord1_[1] = 7;
  coord3_[0] = -7;
  coord3_[1] = 0;

  ASSERT_EQ(coord1_[0], 0);
  ASSERT_EQ(coord1_[1], 7);
  ASSERT_EQ(coord3_[0], -7);
  ASSERT_EQ(coord3_[1], 0);
}

TEST_F(CoordinateTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << coord1_;

  // Multiple Coordinate object representations in the stream.
  os << " " << coord3_ << std::endl;
}

TEST_F(CoordinateTest, Equality) { ASSERT_TRUE(coord1_ == coord2_); }

TEST_F(CoordinateTest, Inequality) {
  ASSERT_TRUE(coord1_ != coord3_);
  ASSERT_TRUE(coord1_ != coord4_);
}

TEST_F(CoordinateTest, Lesser) {
  ASSERT_TRUE(zero_coord_ < coord1_);
  ASSERT_TRUE(coord1_ < coord6_);
  ASSERT_FALSE(coord1_ < coord2_);
  ASSERT_FALSE(coord1_ < coord3_);
}

TEST_F(CoordinateTest, Greater) {
  ASSERT_TRUE(coord1_ > coord3_);
  ASSERT_FALSE(coord1_ > coord4_);
  ASSERT_FALSE(coord1_ > coord2_);
  ASSERT_FALSE(coord1_ > coord6_);
}

TEST_F(CoordinateTest, LesserEqual) {
  ASSERT_TRUE(zero_coord_ <= coord1_);
  ASSERT_TRUE(coord1_ <= coord6_);
  ASSERT_TRUE(coord1_ <= coord2_);
  ASSERT_FALSE(coord1_ <= coord3_);
}

TEST_F(CoordinateTest, GreaterEqual) {
  ASSERT_TRUE(coord1_ >= coord3_);
  ASSERT_FALSE(coord1_ >= coord4_);
  ASSERT_TRUE(coord1_ >= coord2_);
  ASSERT_FALSE(coord1_ >= coord6_);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
