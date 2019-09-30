#include "gtest/gtest.h"

#include "constructs/include/coordinate.h"

namespace {

using morphac::constructs::Coordinate2D;

class CoordinateTest : public ::testing::Test {
 protected:
  CoordinateTest() {}

  void SetUp() override {}

  Coordinate2D zero_coord_{Coordinate2D(0, 0)};
};

TEST_F(CoordinateTest, InitializationCheck) {
  ASSERT_EQ(zero_coord_.get_x(), 0);
  ASSERT_EQ(zero_coord_.get_y(), 0);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
