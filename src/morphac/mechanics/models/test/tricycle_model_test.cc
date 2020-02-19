#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/tricycle_model.h"

namespace {

using std::string;

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::TricycleModel;

class TricycleModelTest : public ::testing::Test {
 protected:
  TricycleModelTest() {}

  void SetUp() override {}
};

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


