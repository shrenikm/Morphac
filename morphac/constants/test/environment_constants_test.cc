#include "constants/include/environment_constants.h"

#include "gtest/gtest.h"

namespace {

using morphac::constants::MapConstants;

class EnvironmentConstantsTest : public ::testing::Test {
 protected:
  EnvironmentConstantsTest() {}

  void SetUp() override {}
};

TEST_F(EnvironmentConstantsTest, MapConstants) {
  // Test Map constants.
  ASSERT_EQ(MapConstants::EMPTY, 0);
  ASSERT_EQ(MapConstants::OBSTACLE, 1);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
