#include "gtest/gtest.h"

#include "constants/include/map_constants.h"

namespace {

using morphac::constants::MapConstants;

class MapConstantsTest : public ::testing::Test {
 protected:
  MapConstantsTest() {}

  void SetUp() override {}

  MapConstants map_constants_;
};

TEST_F(MapConstantsTest, Members) {
  ASSERT_EQ(map_constants_.empty, 0.);
  ASSERT_EQ(map_constants_.obstacle, -1.);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
