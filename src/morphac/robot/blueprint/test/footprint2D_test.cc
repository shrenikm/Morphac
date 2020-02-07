#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "robot/blueprint/include/footprint2D.h"

namespace {

using Eigen::MatrixXd;

using morphac::robot::blueprint::Footprint2D;

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
