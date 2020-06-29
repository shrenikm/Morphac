#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "environment/include/map.h"
#include "simulation/include/playground_state.h"

namespace {

using std::make_unique;
using std::srand;
using std::unique_ptr;

using Eigen::MatrixXd;

using morphac::environment::Map;
using morphac::simulation::PlaygroundState;

class PlaygroundStateTest : public ::testing::Test {
 protected:
  PlaygroundStateTest() {
    // Set random seed for Eigen.
    srand(7);

    playground_state1_ = make_unique<PlaygroundState>(Map(30, 30, 0.1));
    playground_state2_ = make_unique<PlaygroundState>(Map(map_, 0.1));
  }

  void SetUp() override {}

  unique_ptr<PlaygroundState> playground_state1_, playground_state2_;
  MatrixXd map_ = MatrixXd::Random(300, 300);
};

TEST_F(PlaygroundStateTest, GetMap) {
  ASSERT_TRUE(playground_state1_->get_map().get_data().isApprox(
      MatrixXd::Zero(300, 300)));
  ASSERT_EQ(playground_state1_->get_map().get_width(), 30.);
  ASSERT_EQ(playground_state1_->get_map().get_height(), 30.);
  ASSERT_EQ(playground_state1_->get_map().get_resolution(), 0.1);

  ASSERT_TRUE(playground_state2_->get_map().get_data().isApprox(map_));
  ASSERT_EQ(playground_state2_->get_map().get_width(), 30.);
  ASSERT_EQ(playground_state2_->get_map().get_height(), 30.);
  ASSERT_EQ(playground_state2_->get_map().get_resolution(), 0.1);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
