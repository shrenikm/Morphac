#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "mechanics/models/include/dubin_model.h"

namespace {

using std::string;

using Eigen::VectorXd;

using morphac::mechanics::models::DubinModel;

class DubinModelTest : public ::testing::Test {
 protected:
  DubinModelTest() {}

  void SetUp() override {}
};

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
