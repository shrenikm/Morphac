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

  Coordinate<int> default_coord_int_{};
  Coordinate<int> zero_coord_int_{1, 2};
  Coordinate<int> coord1_int_{2, 3};
  // Copy constructor.
  Coordinate<int> coord2_int_ = coord1_int_;
  Coordinate<int> coord3_int_{-1, 4};
  Coordinate<int> coord4_int_{2, 2};
  // Copy constructor.
  Coordinate<int> coord5_int_{Coordinate<int>(3, 2)};
  Coordinate<int> coord6_int_{Coordinate<int>(2, 5)};

  Coordinate<double> default_coord_double_{};
  Coordinate<double> zero_coord_double_{1.0, 2.0};
  Coordinate<double> coord1_double_{2.0, 3.0};
  // Copy constructor.
  Coordinate<double> coord2_double_ = coord1_double_;
  Coordinate<double> coord3_double_{-1.5, 4.7};
  Coordinate<double> coord4_double_{2.6, 2.1};
  // Copy constructor.
  Coordinate<double> coord5_double_{Coordinate<double>(3.1, 2.8)};
  Coordinate<double> coord6_double_{Coordinate<double>(2.2, 5.9)};
};

TEST_F(CoordinateTest, DefaultObject) {
  ASSERT_EQ(default_coord_int_.get_x(), 0);
  ASSERT_EQ(default_coord_int_.get_y(), 0);
  ASSERT_DOUBLE_EQ(default_coord_double_.get_x(), 0.0);
  ASSERT_DOUBLE_EQ(default_coord_double_.get_y(), 0.0);
}

TEST_F(CoordinateTest, Initialization) {
  ASSERT_EQ(zero_coord_int_.get_x(), 1);
  ASSERT_EQ(zero_coord_int_.get_y(), 2);
  ASSERT_DOUBLE_EQ(zero_coord_double_.get_x(), 1.0);
  ASSERT_DOUBLE_EQ(zero_coord_double_.get_y(), 2.0);
}

TEST_F(CoordinateTest, GetData) {
  Matrix<int, 2, 1> coord_int_data = coord1_int_.get_data();
  ASSERT_EQ(coord_int_data(0), 2);
  ASSERT_EQ(coord_int_data(1), 3);

  VectorXd coord_double_data = coord1_double_.get_data();
  ASSERT_EQ(coord_double_data.size(), 2);
  ASSERT_EQ(coord_double_data(0), 2.);
  ASSERT_EQ(coord_double_data(1), 3.);
}

TEST_F(CoordinateTest, SetData) {
  Matrix<int, 2, 1> coord_int_data;
  coord_int_data << -2, -3;
  coord1_int_.set_data(coord_int_data);

  ASSERT_EQ(coord1_int_.get_x(), -2);
  ASSERT_EQ(coord1_int_.get_y(), -3);

  VectorXd coord_double_data(2);
  coord_double_data << -2, -3;
  coord1_double_.set_data(coord_double_data);

  ASSERT_EQ(coord1_double_.get_x(), -2);
  ASSERT_EQ(coord1_double_.get_y(), -3);
}

TEST_F(CoordinateTest, Addition) {
  Coordinate<int> result_int = coord1_int_ + coord3_int_;
  Coordinate<double> result_double = coord1_double_ + coord3_double_;

  ASSERT_EQ(result_int.get_x(), 1);
  ASSERT_EQ(result_int.get_y(), 7);
  ASSERT_DOUBLE_EQ(result_double.get_x(), 0.5);
  ASSERT_DOUBLE_EQ(result_double.get_y(), 7.7);

  coord1_int_ += coord3_int_;
  coord1_double_ += coord3_double_;

  ASSERT_EQ(coord1_int_.get_x(), 1);
  ASSERT_EQ(coord1_int_.get_y(), 7);
  ASSERT_DOUBLE_EQ(coord1_double_.get_x(), 0.5);
  ASSERT_DOUBLE_EQ(coord1_double_.get_y(), 7.7);
}

TEST_F(CoordinateTest, Subtraction) {
  Coordinate<int> result_int = coord1_int_ - coord3_int_;
  Coordinate<double> result_double = coord1_double_ - coord3_double_;

  ASSERT_EQ(result_int.get_x(), 3);
  ASSERT_EQ(result_int.get_y(), -1);
  ASSERT_DOUBLE_EQ(result_double.get_x(), 3.5);
  ASSERT_DOUBLE_EQ(result_double.get_y(), -1.7);

  coord1_int_ -= coord3_int_;
  coord1_double_ -= coord3_double_;

  ASSERT_EQ(coord1_int_.get_x(), 3);
  ASSERT_EQ(coord1_int_.get_y(), -1);
  ASSERT_DOUBLE_EQ(coord1_double_.get_x(), 3.5);
  ASSERT_DOUBLE_EQ(coord1_double_.get_y(), -1.7);
}

TEST_F(CoordinateTest, Multiplication) {
  Coordinate<int> result_int1 = coord1_int_ * (-2);
  Coordinate<int> result_int2 = -2 * coord1_int_;

  Coordinate<double> result_double1 = 1.5 * coord3_double_;

  ASSERT_EQ(result_int1.get_x(), -4);
  ASSERT_EQ(result_int1.get_y(), -6);
  ASSERT_EQ(result_int2.get_x(), -4);
  ASSERT_EQ(result_int2.get_y(), -6);
  ASSERT_DOUBLE_EQ(result_double1.get_x(), -2.25);
  ASSERT_DOUBLE_EQ(result_double1.get_y(), 7.05);

  coord1_int_ *= 3;
  coord3_double_ *= -2;
  ASSERT_EQ(coord1_int_.get_x(), 6);
  ASSERT_EQ(coord1_int_.get_y(), 9);
  ASSERT_DOUBLE_EQ(coord3_double_.get_x(), 3.);
  ASSERT_DOUBLE_EQ(coord3_double_.get_y(), -9.4);
}

TEST_F(CoordinateTest, GetAt) {
  ASSERT_EQ(coord1_int_[0], 2);
  ASSERT_EQ(coord1_int_[1], 3);
  ASSERT_DOUBLE_EQ(coord3_double_[0], -1.5);
  ASSERT_DOUBLE_EQ(coord3_double_[1], 4.7);
}

TEST_F(CoordinateTest, InvalidGetAt) {
  ASSERT_THROW(coord1_int_[-1], std::out_of_range);
  ASSERT_THROW(coord1_int_[2], std::out_of_range);
  ASSERT_THROW(coord3_double_[-1], std::out_of_range);
  ASSERT_THROW(coord3_double_[2], std::out_of_range);
}

TEST_F(CoordinateTest, SetAt) {
  coord1_int_[0] = 0;
  coord1_int_[1] = 7;
  coord3_int_[0] = -7;
  coord3_int_[1] = 0;

  ASSERT_EQ(coord1_int_[0], 0);
  ASSERT_EQ(coord1_int_[1], 7);
  ASSERT_EQ(coord3_int_[0], -7);
  ASSERT_EQ(coord3_int_[1], 0);
}

TEST_F(CoordinateTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << coord1_int_;

  // Multiple Coordinate object representations in the stream.
  os << " " << coord3_double_ << std::endl;
}

TEST_F(CoordinateTest, Equality) {
  ASSERT_TRUE(coord1_int_ == coord2_int_);
  ASSERT_TRUE(coord1_double_ == coord2_double_);
}

TEST_F(CoordinateTest, Inequality) {
  ASSERT_TRUE(coord1_int_ != coord3_int_);
  ASSERT_TRUE(coord1_int_ != coord4_int_);
  ASSERT_TRUE(coord1_double_ != coord3_double_);
  ASSERT_TRUE(coord1_double_ != coord4_double_);
}

TEST_F(CoordinateTest, Lesser) {
  ASSERT_TRUE(zero_coord_int_ < coord1_int_);
  ASSERT_TRUE(coord1_int_ < coord6_int_);
  ASSERT_FALSE(coord1_int_ < coord2_int_);
  ASSERT_FALSE(coord1_int_ < coord3_int_);
  ASSERT_TRUE(zero_coord_double_ < coord1_double_);
  ASSERT_TRUE(coord1_double_ < coord6_double_);
  ASSERT_FALSE(coord1_double_ < coord2_double_);
  ASSERT_FALSE(coord1_double_ < coord3_double_);
}

TEST_F(CoordinateTest, Greater) {
  ASSERT_TRUE(coord1_int_ > coord3_int_);
  ASSERT_TRUE(coord1_int_ > coord4_int_);
  ASSERT_FALSE(coord1_int_ > coord2_int_);
  ASSERT_FALSE(coord1_int_ > coord6_int_);
  ASSERT_TRUE(coord1_double_ > coord3_double_);
  ASSERT_FALSE(coord1_double_ > coord4_double_);
  ASSERT_FALSE(coord1_double_ > coord2_double_);
  ASSERT_FALSE(coord1_double_ > coord6_double_);
}

TEST_F(CoordinateTest, LesserEqual) {
  ASSERT_TRUE(zero_coord_int_ <= coord1_int_);
  ASSERT_TRUE(coord1_int_ <= coord6_int_);
  ASSERT_TRUE(coord1_int_ <= coord2_int_);
  ASSERT_FALSE(coord1_int_ <= coord3_int_);
  ASSERT_TRUE(zero_coord_double_ <= coord1_double_);
  ASSERT_TRUE(coord1_double_ <= coord6_double_);
  ASSERT_TRUE(coord1_double_ <= coord2_double_);
  ASSERT_FALSE(coord1_double_ <= coord3_double_);
}

TEST_F(CoordinateTest, GreaterEqual) {
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
