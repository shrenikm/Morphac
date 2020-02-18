#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/diffdrive_model.h"

namespace {

using std::string;

using Eigen::MatrixXd;
using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::mechanics::models::DiffDriveModel;

class DiffDriveModelTest : public ::testing::Test {
 protected:
  DiffDriveModelTest() {}

  void SetUp() override {}
};

TEST_F(DiffDriveModelTest, Sizes) {
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

