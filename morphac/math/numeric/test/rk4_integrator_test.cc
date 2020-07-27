#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "math/numeric/include/integrator.h"
#include "math/numeric/include/rk4_integrator.h"
#include "mechanics/models/include/diffdrive_model.h"

namespace {

using std::abs;
using std::cos;
using std::make_unique;
using std::pow;
using std::sin;
using std::srand;
using std::unique_ptr;

using Eigen::VectorXd;

using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::math::numeric::RK4Integrator;
using morphac::math::numeric::Integrator;
using morphac::mechanics::models::DiffDriveModel;
using morphac::mechanics::models::KinematicModel;

class RK4IntegratorTest : public ::testing::Test {
 protected:
  RK4IntegratorTest() {
    // Set random seed for Eigen.
    srand(7);
    diffdrive_model_ = make_unique<DiffDriveModel>(0.1, 0.2);
    rk4_integrator_ = make_unique<RK4Integrator>(*diffdrive_model_);
  }

  void SetUp() override {}

  unique_ptr<DiffDriveModel> diffdrive_model_;
  unique_ptr<RK4Integrator> rk4_integrator_;
};

TEST_F(RK4IntegratorTest, TrivialStep) {
  // Testing trivial step values with the DiffDriveModel.
  DiffDriveModel diffdrive_model{1.2, 2.5};
  RK4Integrator rk4_integrator{diffdrive_model};

  // Derivative is zero when the wheel velocities are zero.
  auto derivative1 =
      rk4_integrator.Step(State({1, 1, 1}, {}), ControlInput({0, 0}), 0.5);

  // Derivative is zero when the time step is zero.
  auto derivative2 = rk4_integrator.Step(State(3, 0), ControlInput({1, 1}), 0.);

  ASSERT_TRUE(derivative1.get_data().isApprox(VectorXd::Ones(3)));
  ASSERT_TRUE(derivative2.get_data().isApprox(VectorXd::Zero(3)));
}

TEST_F(RK4IntegratorTest, Step) {
  // Linear velocity = r * (wr + wl) / 2
  // Angular vellocity = r * (wr - wl) / l

  // Linear velocity = 0.05
  // Angular velocity = 0
  ControlInput control_input1({0.5, 0.5});
  // Linear velocity = -0.05
  // Angular velocity = 0
  ControlInput control_input2({-0.5, -0.5});
  // Linear velocity = 0
  // Angular velocity = 0.01
  ControlInput control_input3({-0.5, 0.5});
  // Linear velocity = 0
  // Angular velocity = -0.01
  ControlInput control_input4({0.5, -0.5});

  // First we test for when the robot is facing the x axis.
  // 0.5 rad/s for 0.1 seconds moves us forward by 0.05 * 0.1 seconds
  auto updated_state =
      rk4_integrator_->Step(State({0, 0, 0}, {}), control_input1, 0.1);
  ASSERT_TRUE(updated_state == State({0.005, 0, 0}, {}));

  // Moving backwards.
  updated_state =
      rk4_integrator_->Step(State({0, 0, 0}, {}), control_input2, 0.1);
  ASSERT_TRUE(updated_state == State({-0.005, 0, 0}, {}));

  // Turning in place to the left.
  // 0.5 rad/s for 0.1 seconds. (Angular velocity so only theta changes).
  updated_state =
      rk4_integrator_->Step(State({0, 0, 0}, {}), control_input3, 0.1);
  ASSERT_TRUE(updated_state == State({0, 0, 0.05}, {}));

  // Turning in place to the right.
  updated_state =
      rk4_integrator_->Step(State({0, 0, 0}, {}), control_input4, 0.1);
  ASSERT_TRUE(updated_state == State({0, 0, -0.05}, {}));

  // Straight line facing a 45 degree angle.
  updated_state =
      rk4_integrator_->Step(State({1., 2., M_PI / 4}, {}), control_input1, 0.1);
  ASSERT_TRUE(updated_state == State({1 + 0.005 * cos(M_PI / 4),
                                      2 + 0.005 * sin(M_PI / 4), M_PI / 4},
                                     {}));

  // Angled straight line backwards.
  updated_state =
      rk4_integrator_->Step(State({1., 2., M_PI / 4}, {}), control_input2, 0.1);
  ASSERT_TRUE(updated_state == State({1 - 0.005 * cos(M_PI / 4),
                                      2 - 0.005 * sin(M_PI / 4), M_PI / 4},
                                     {}));
}

TEST_F(RK4IntegratorTest, Integrate) {
  // Linear velocity = 0.05
  // Angular velocity = 0
  ControlInput control_input1({0.5, 0.5});
  // Linear velocity = -0.05
  // Angular velocity = 0
  ControlInput control_input2({-0.5, -0.5});
  // Linear velocity = 0
  // Angular velocity = 0.01
  ControlInput control_input3({-0.5, 0.5});
  // Linear velocity = 0
  // Angular velocity = -0.01
  ControlInput control_input4({0.5, -0.5});

  // Integrating forward.
  auto updated_state =
      rk4_integrator_->Integrate(State(3, 0), control_input1, 10, 0.01);
  ASSERT_TRUE(updated_state == State({0.5, 0, 0}, {}));

  // Backward.
  updated_state =
      rk4_integrator_->Integrate(State(3, 0), control_input2, 10, 0.01);
  ASSERT_TRUE(updated_state == State({-0.5, 0, 0}, {}));

  // Turn in place by 90 degrees to the left. For an angular velocity (theta) of
  // 0.5 (using control_input3), we need to turn by (pi/2) / 0.5 seconds.
  updated_state =
      rk4_integrator_->Integrate(State(3, 0), control_input3, M_PI, 0.01);
  ASSERT_TRUE(updated_state == State({0, 0, M_PI / 2}, {}));

  // Turn in place by 270 degrees to the right. For an angular velocity (theta)
  // of 0.5 (using control_input4), we need to turn by (3*pi/2) / 0.5 seconds.
  updated_state =
      rk4_integrator_->Integrate(State(3, 0), control_input4, 3 * M_PI, 0.01);
  // As the output state is normalized, the final angle would be positive as it
  // lies in the second quadrant.
  ASSERT_TRUE(updated_state == State({0, 0, M_PI / 2}, {}));

  // Trace a circular path and come back to the starting position.
  updated_state =
      rk4_integrator_->Integrate(State({0, 0, M_PI / 2}, {}),
                                 ControlInput({1, 2}), (2 * M_PI) / 0.5, 0.01);
  ASSERT_TRUE(updated_state == State({0, 0, M_PI / 2}, {}));
}

TEST_F(RK4IntegratorTest, OrderOfIntegration) {
  // Testing the order of integration.

  // Letting the robot run in circles for a few full rounds.
  // Distance from the robot center to the icc is given by
  // R = (l / 2) * (wl + wr) / (wr - wl)
  // R = 0.3 in this case. Hence when the robot stops after rotating for
  // 2*pi + pi/2 degrees, the x and y coordinate must be 0.3 meters away. The
  // y coordinate would also be negative. As we start with an angle of zero and
  // traverse a net angle of pi/2 clockwise, the final angle would be -pi/2.
  double true_x = 0.3;
  double true_y = -0.3;
  double true_theta = -M_PI / 2;

  // Integrating using different dt values.
  // As it is a fourth order integrator, the absolute differences between the
  // computed and actual values must be of the order dt^4.
  for (int i = 1; i <= 3; ++i) {
    double dt = 1. / pow(10, i);
    auto updated_state = rk4_integrator_->Integrate(
        State(3, 0), ControlInput({10, 5}), (4 * M_PI + M_PI / 2) / 2.5, dt);
    ASSERT_TRUE(abs(updated_state[0] - true_x) < pow(dt, 4));
    ASSERT_TRUE(abs(updated_state[1] - true_y) < pow(dt, 4));
    ASSERT_TRUE(abs(updated_state[2] - true_theta) < pow(dt, 4));
    std::cout << updated_state << std::endl;
  }
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
