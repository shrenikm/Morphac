#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "math/numeric/include/euler_integrator.h"
#include "math/numeric/include/integrator.h"
#include "mechanics/models/include/diffdrive_model.h"

namespace {

using std::srand;

using Eigen::VectorXd;

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::math::numeric::EulerIntegrator;
using morphac::math::numeric::Integrator;
using morphac::mechanics::models::DiffDriveModel;
using morphac::mechanics::models::KinematicModel;

class EulerIntegratorTest : public ::testing::Test {
 protected:
  EulerIntegratorTest() {}

  void SetUp() override { srand(7); }
};

TEST_F(EulerIntegratorTest, TrivialStep) {
  // Testing trivial step values with the DiffDriveModel.
  DiffDriveModel diffdrive_model{1.2, 2.5};
  EulerIntegrator euler_integrator{diffdrive_model};

  auto derivative1 =
      euler_integrator.Step(State(VectorXd::Ones(3), VectorXd::Zero(0)),
                            Input(VectorXd::Zero(2)), 0.5);

  auto derivative2 =
      euler_integrator.Step(State(VectorXd::Zero(3), VectorXd::Zero(0)),
                            Input(VectorXd::Ones(2)), 0.);

  ASSERT_TRUE(derivative1.get_state_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(derivative2.get_state_vector().isApprox(VectorXd::Zero(3)));
}

TEST_F(EulerIntegratorTest, Step) {
  // Testing actual step computation using the DiffDriveModel.
  DiffDriveModel diffdrive_model{0.1, 0.5};
  EulerIntegrator euler_integrator{diffdrive_model};

  //Input input({1, 2});
  //std::cout << input.get_input_vector() << std::endl;

  // Testing for horizontal movement. If both wheels move at 0.1 rad/s TODO
  //euler_integrator.Step(State(3, 0),
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
