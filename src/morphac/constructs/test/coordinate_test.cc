#include "gtest/gtest.h"

#include "constructs/include/coordinate.h"

namespace {

using morphac::constructs::Coordinate2D;

class Coordinate2DTest : public ::testing::Test {
 protected:
  Coordinate2DTest() {}

  void SetUp() override {}

  Coordinate2D<int> default_coord_int_{Coordinate2D<int>()};
  Coordinate2D<int> zero_coord_int_{Coordinate2D<int>(1, 2)};
  Coordinate2D<int> coord1_int_{Coordinate2D<int>(2, 3)};
  Coordinate2D<int> coord2_int_ = coord1_int_;
  Coordinate2D<int> coord3_int_{Coordinate2D<int>(-1, 4)};
  Coordinate2D<int> coord4_int_{Coordinate2D<int>(2, 2)};
  Coordinate2D<int> coord5_int_{Coordinate2D<int>(3, 2)};
  Coordinate2D<int> coord6_int_{Coordinate2D<int>(2, 5)};

  Coordinate2D<double> default_coord_double_{Coordinate2D<double>()};
  Coordinate2D<double> zero_coord_double_{Coordinate2D<double>(1.0, 2.0)};
  Coordinate2D<double> coord1_double_{Coordinate2D<double>(2.0, 3.0)};
  Coordinate2D<double> coord2_double_ = coord1_double_;
  Coordinate2D<double> coord3_double_{Coordinate2D<double>(-1.5, 4.7)};
  Coordinate2D<double> coord4_double_{Coordinate2D<double>(2.6, 2.1)};
  Coordinate2D<double> coord5_double_{Coordinate2D<double>(3.1, 2.8)};
  Coordinate2D<double> coord6_double_{Coordinate2D<double>(2.2, 5.9)};
};

TEST_F(Coordinate2DTest, DefaultObject) {
  ASSERT_EQ(default_coord_int_.get_x(), 0);
  ASSERT_EQ(default_coord_int_.get_y(), 0);
  ASSERT_DOUBLE_EQ(default_coord_double_.get_x(), 0.0);
  ASSERT_DOUBLE_EQ(default_coord_double_.get_y(), 0.0);
}

TEST_F(Coordinate2DTest, Initialization) {
  ASSERT_EQ(zero_coord_int_.get_x(), 1);
  ASSERT_EQ(zero_coord_int_.get_y(), 2);
  ASSERT_DOUBLE_EQ(zero_coord_double_.get_x(), 1.0);
  ASSERT_DOUBLE_EQ(zero_coord_double_.get_y(), 2.0);
}

TEST_F(Coordinate2DTest, OperatorCompoundAdd) {
  coord1_int_ += coord3_int_;
  coord1_double_ += coord3_double_;
  ASSERT_EQ(coord1_int_.get_x(), 1);
  ASSERT_EQ(coord1_int_.get_y(), 7);
  ASSERT_DOUBLE_EQ(coord1_double_.get_x(), 0.5);
  ASSERT_DOUBLE_EQ(coord1_double_.get_y(), 7.7);
}

TEST_F(Coordinate2DTest, OperatorAdd) {
  Coordinate2D<int> result_int = coord1_int_ + coord3_int_;
  Coordinate2D<double> result_double = coord1_double_ + coord3_double_;
  ASSERT_EQ(result_int.get_x(), 1);
  ASSERT_EQ(result_int.get_y(), 7);
  ASSERT_DOUBLE_EQ(result_double.get_x(), 0.5);
  ASSERT_DOUBLE_EQ(result_double.get_y(), 7.7);
}

TEST_F(Coordinate2DTest, OperatorCompoundSubtract) {
  coord1_int_ -= coord3_int_;
  coord1_double_ -= coord3_double_;
  ASSERT_EQ(coord1_int_.get_x(), 3);
  ASSERT_EQ(coord1_int_.get_y(), -1);
  ASSERT_DOUBLE_EQ(coord1_double_.get_x(), 3.5);
  ASSERT_DOUBLE_EQ(coord1_double_.get_y(), -1.7);
}

TEST_F(Coordinate2DTest, OperatorSubtract) {
  Coordinate2D<int> result_int = coord1_int_ - coord3_int_;
  Coordinate2D<double> result_double = coord1_double_ - coord3_double_;
  ASSERT_EQ(result_int.get_x(), 3);
  ASSERT_EQ(result_int.get_y(), -1);
  ASSERT_DOUBLE_EQ(result_double.get_x(), 3.5);
  ASSERT_DOUBLE_EQ(result_double.get_y(), -1.7);
}

TEST_F(Coordinate2DTest, OperatorEqual) {
  ASSERT_TRUE(coord1_int_ == coord2_int_);
  ASSERT_TRUE(coord1_double_ == coord2_double_);
}

TEST_F(Coordinate2DTest, OperatorNotEqual) {
  ASSERT_TRUE(coord1_int_ != coord3_int_);
  ASSERT_TRUE(coord1_int_ != coord4_int_);
  ASSERT_TRUE(coord1_double_ != coord3_double_);
  ASSERT_TRUE(coord1_double_ != coord4_double_);
}

TEST_F(Coordinate2DTest, OperatorLess) {
  ASSERT_TRUE(zero_coord_int_ < coord1_int_);
  ASSERT_TRUE(coord1_int_ < coord6_int_);
  ASSERT_FALSE(coord1_int_ < coord2_int_);
  ASSERT_FALSE(coord1_int_ < coord3_int_);
  ASSERT_TRUE(zero_coord_double_ < coord1_double_);
  ASSERT_TRUE(coord1_double_ < coord6_double_);
  ASSERT_FALSE(coord1_double_ < coord2_double_);
  ASSERT_FALSE(coord1_double_ < coord3_double_);
}

TEST_F(Coordinate2DTest, OperatorGreater) {
  ASSERT_TRUE(coord1_int_ > coord3_int_);
  ASSERT_TRUE(coord1_int_ > coord4_int_);
  ASSERT_FALSE(coord1_int_ > coord2_int_);
  ASSERT_FALSE(coord1_int_ > coord6_int_);
  ASSERT_TRUE(coord1_double_ > coord3_double_);
  ASSERT_FALSE(coord1_double_ > coord4_double_);
  ASSERT_FALSE(coord1_double_ > coord2_double_);
  ASSERT_FALSE(coord1_double_ > coord6_double_);
}

TEST_F(Coordinate2DTest, OperatorLesserEqual) {
  ASSERT_TRUE(zero_coord_int_ <= coord1_int_);
  ASSERT_TRUE(coord1_int_ <= coord6_int_);
  ASSERT_TRUE(coord1_int_ <= coord2_int_);
  ASSERT_FALSE(coord1_int_ <= coord3_int_);
  ASSERT_TRUE(zero_coord_double_ <= coord1_double_);
  ASSERT_TRUE(coord1_double_ <= coord6_double_);
  ASSERT_TRUE(coord1_double_ <= coord2_double_);
  ASSERT_FALSE(coord1_double_ <= coord3_double_);
}

TEST_F(Coordinate2DTest, OperatorGreaterEqual) {
  ASSERT_TRUE(coord1_int_ >= coord3_int_);
  ASSERT_TRUE(coord1_int_ >= coord4_int_);
  ASSERT_TRUE(coord1_int_ >= coord2_int_);
  ASSERT_FALSE(coord1_int_ >= coord6_int_);
  ASSERT_TRUE(coord1_double_ >= coord3_double_);
  ASSERT_FALSE(coord1_double_ >= coord4_double_);
  ASSERT_TRUE(coord1_double_ >= coord2_double_);
  ASSERT_FALSE(coord1_double_ >= coord6_double_);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
