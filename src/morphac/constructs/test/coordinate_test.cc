#include "gtest/gtest.h"

#include "constructs/include/coordinate.h"

namespace {

using morphac::constructs::Coordinate2D;

class CoordinateTest : public ::testing::Test {
 protected:
  CoordinateTest() {}

  void SetUp() override {}

  Coordinate2D default_coord_{Coordinate2D()};
  Coordinate2D zero_coord_{Coordinate2D(1, 2)};
  Coordinate2D coord1_{Coordinate2D(2, 3)};

  // Copy constructor
  Coordinate2D coord2_ = coord1_;

  Coordinate2D coord3_{Coordinate2D(-1, 4)};
  Coordinate2D coord4_{Coordinate2D(2, 2)};
  Coordinate2D coord5_{Coordinate2D(3, 2)};
  Coordinate2D coord6_{Coordinate2D(2, 5)};
};

TEST_F(CoordinateTest, DefaultObject) {
  ASSERT_EQ(default_coord_.get_x(), 0);
  ASSERT_EQ(default_coord_.get_y(), 0);
}

TEST_F(CoordinateTest, Initialization) {
  ASSERT_EQ(zero_coord_.get_x(), 1);
  ASSERT_EQ(zero_coord_.get_y(), 2);
}

TEST_F(CoordinateTest, OperatorCompoundAdd) {
  coord1_ += coord3_;
  ASSERT_EQ(coord1_.get_x(), 1);
  ASSERT_EQ(coord1_.get_y(), 7);
}

TEST_F(CoordinateTest, OperatorAdd) {
  Coordinate2D result = coord1_ + coord3_;
  ASSERT_EQ(result.get_x(), 1);
  ASSERT_EQ(result.get_y(), 7);
}

TEST_F(CoordinateTest, OperatorCompoundSubtract) {
  coord1_ -= coord3_;
  ASSERT_EQ(coord1_.get_x(), 3);
  ASSERT_EQ(coord1_.get_y(), -1);
}

TEST_F(CoordinateTest, OperatorSubtract) {
  Coordinate2D result = coord1_ - coord3_;
  ASSERT_EQ(result.get_x(), 3);
  ASSERT_EQ(result.get_y(), -1);
}

TEST_F(CoordinateTest, OperatorEqual) { ASSERT_TRUE(coord1_ == coord2_); }

TEST_F(CoordinateTest, OperatorNotEqual) {
  ASSERT_TRUE(coord1_ != coord3_);
  ASSERT_TRUE(coord1_ != coord4_);
}

TEST_F(CoordinateTest, OperatorLess) {
  ASSERT_TRUE(zero_coord_ < coord1_);
  ASSERT_TRUE(coord1_ < coord6_);
  ASSERT_FALSE(coord1_ < coord2_);
  ASSERT_FALSE(coord1_ < coord3_);
}

TEST_F(CoordinateTest, OperatorGreater) {
  ASSERT_TRUE(coord1_ > coord3_);
  ASSERT_TRUE(coord1_ > coord4_);
  ASSERT_FALSE(coord1_ > coord2_);
  ASSERT_FALSE(coord1_ > coord6_);
}

TEST_F(CoordinateTest, OperatorLesserEqual) {
  ASSERT_TRUE(zero_coord_ <= coord1_);
  ASSERT_TRUE(coord1_ <= coord6_);
  ASSERT_TRUE(coord1_ <= coord2_);
  ASSERT_FALSE(coord1_ <= coord3_);
}

TEST_F(CoordinateTest, OperatorGreaterEqual) {
  ASSERT_TRUE(coord1_ >= coord3_);
  ASSERT_TRUE(coord1_ >= coord4_);
  ASSERT_TRUE(coord1_ >= coord2_);
  ASSERT_FALSE(coord1_ >= coord6_);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
