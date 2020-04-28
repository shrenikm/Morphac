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

  // Derivative is zero when the wheel velocities are zero.
  auto derivative1 =
      euler_integrator.Step(State({1, 1, 1}, {}), Input({0, 0}), 0.5);

  // Derivative is zero when the time step is zero.
  auto derivative2 = euler_integrator.Step(State(3, 0), Input({1, 1}), 0.);

  ASSERT_TRUE(derivative1.get_state_vector().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(derivative2.get_state_vector().isApprox(VectorXd::Zero(3)));
}

TEST_F(EulerIntegratorTest, Step) {
  // Testing actual step computation using the DiffDriveModel.
  DiffDriveModel diffdrive_model{0.1, 0.2};
  EulerIntegrator euler_integrator{diffdrive_model};

  // Testing for horizontal movement. If both wheels move at 0.5 rad/s, the
  // angular velocity is zero (Doesn't turn) and the linear velocity is
  // v * (wr + wl)/2 = 0.1 * (0.5 + 0.5)/2 = 0.05
  Input input({0.5, 0.5});

  // First we test for when the robot is facing the x axis.
  // auto derivative1 = euler_integrator.Step(State({0, 0, 0}, {}), input,
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
