#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "math/numeric/include/euler_integrator.h"
#include "math/numeric/include/integrator.h"
#include "mechanics/models/include/diffdrive_model.h"

namespace {

using std::cos;
using std::sin;
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
  DiffDriveModel diffdrive_model{0.1, 0.2};
  EulerIntegrator euler_integrator{diffdrive_model};

  // Linear velocity = r * (wr + wl) / 2
  // Angular vellocity = r * (wr - wl) / l

  // Linear velocity = 0.05
  // Angular velocity = 0
  Input input1({0.5, 0.5});
  // Linear velocity = -0.05
  // Angular velocity = 0
  Input input2({-0.5, -0.5});
  // Linear velocity = 0
  // Angular velocity = 0.01
  Input input3({-0.5, 0.5});
  // Linear velocity = 0
  // Angular velocity = -0.01
  Input input4({0.5, -0.5});

  // First we test for when the robot is facing the x axis.
  // 0.5 rad/s for 0.1 seconds moves us forward by 0.05 * 0.1 seconds
  auto updated_state = euler_integrator.Step(State({0, 0, 0}, {}), input1, 0.1);
  ASSERT_TRUE(updated_state == State({0.005, 0, 0}, {}));

  // Moving backwards.
  updated_state = euler_integrator.Step(State({0, 0, 0}, {}), input2, 0.1);
  ASSERT_TRUE(updated_state == State({-0.005, 0, 0}, {}));

  // Turning in place to the left.
  // 0.5 rad/s for 0.1 seconds. (Angular velocity so only theta changes).
  updated_state = euler_integrator.Step(State({0, 0, 0}, {}), input3, 0.1);
  ASSERT_TRUE(updated_state == State({0, 0, 0.05}, {}));

  // Turning in place to the right.
  updated_state = euler_integrator.Step(State({0, 0, 0}, {}), input4, 0.1);
  ASSERT_TRUE(updated_state == State({0, 0, -0.05}, {}));

  // Straight line facing a 45 degree angle.
  updated_state =
      euler_integrator.Step(State({1., 2., M_PI / 4}, {}), input1, 0.1);
  ASSERT_TRUE(updated_state == State({1 + 0.005 * cos(M_PI / 4),
                                      2 + 0.005 * sin(M_PI / 4), M_PI / 4},
                                     {}));

  // Angled straight line backwards.
  updated_state =
      euler_integrator.Step(State({1., 2., M_PI / 4}, {}), input2, 0.1);
  ASSERT_TRUE(updated_state == State({1 - 0.005 * cos(M_PI / 4),
                                      2 - 0.005 * sin(M_PI / 4), M_PI / 4},
                                     {}));
}

TEST_F(EulerIntegratorTest, Integrate) {
  DiffDriveModel diffdrive_model{0.1, 0.2};
  EulerIntegrator euler_integrator{diffdrive_model};

  // Linear velocity = 0.05
  // Angular velocity = 0
  Input input1({0.5, 0.5});
  // Linear velocity = -0.05
  // Angular velocity = 0
  Input input2({-0.5, -0.5});
  // Linear velocity = 0
  // Angular velocity = 0.01
  Input input3({-0.5, 0.5});
  // Linear velocity = 0
  // Angular velocity = -0.01
  Input input4({0.5, -0.5});

  // Integrating forward.
  auto updated_state =
      euler_integrator.Integrate(State(3, 0), input1, 10, 0.001);
  ASSERT_TRUE(updated_state == State({0.5, 0, 0}, {}));

  // Backward.
  updated_state = euler_integrator.Integrate(State(3, 0), input2, 10, 0.001);
  ASSERT_TRUE(updated_state == State({-0.5, 0, 0}, {}));

  // Turn in place by 45 degrees to the left. For an angular velocity (theta) of
  // 0.5 (using input3), we need to turn by (pi/2) / 0.5 seconds.
  updated_state = euler_integrator.Integrate(State(3, 0), input3, M_PI, 0.001);
  ASSERT_TRUE(updated_state == State({0, 0, M_PI / 2}, {}));

  // Turn in place by 135 degrees to the right. For an angular velocity (theta)
  // of 0.5 (using input4), we need to turn by (3*pi/2) / 0.5 seconds.
  updated_state =
      euler_integrator.Integrate(State(3, 0), input4, 3 * M_PI, 0.001);
  ASSERT_TRUE(updated_state == State({0, 0, -3 * M_PI / 2}, {}));

  // Trace a circular path and come back to the starting position.
  updated_state = euler_integrator.Integrate(
      State({0, 0, M_PI / 2}, {}), Input({2, 1}), (2 * M_PI) / 0.1, 0.001);
  std::cout << updated_state << std::endl;
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
