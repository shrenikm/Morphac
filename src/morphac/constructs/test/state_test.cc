#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "constructs/include/state.h"

namespace {

using std::make_unique;
using std::move;
using std::unique_ptr;

using Eigen::VectorXd;

using morphac::constructs::Pose;
using morphac::constructs::Velocity;
using morphac::constructs::State;

class StateTest : public ::testing::Test {
 protected:
  StateTest() {}

  void SetUp() override {}
};

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

