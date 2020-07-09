#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "simulation/playground/include/playground_spec.h"

namespace {

using morphac::simulation::playground::PlaygroundSpec;

class PlaygroundSpecTest : public ::testing::Test {
 protected:
  PlaygroundSpecTest() {}

  void SetUp() override {}

  PlaygroundSpec playground_spec1_{"playground1", 0.1, 500, 500};
  PlaygroundSpec playground_spec2_{"playground2", 0.05, 800, 400};
};

TEST_F(PlaygroundSpecTest, Members) {
  ASSERT_EQ(playground_spec1_.name, "playground1");
  ASSERT_EQ(playground_spec1_.dt, 0.1);
  ASSERT_EQ(playground_spec1_.gui_width, 500);
  ASSERT_EQ(playground_spec1_.gui_height, 500);

  ASSERT_EQ(playground_spec2_.name, "playground2");
  ASSERT_EQ(playground_spec2_.dt, 0.05);
  ASSERT_EQ(playground_spec2_.gui_width, 800);
  ASSERT_EQ(playground_spec2_.gui_height, 400);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

