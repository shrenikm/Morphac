#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "math/numeric/include/integrator.h"
#include "mechanics/models/include/diffdrive_model.h"

namespace {

using std::pow;
using std::srand;

using Eigen::VectorXd;

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::math::numeric::Integrator;
using morphac::mechanics::models::DiffDriveModel;
using morphac::mechanics::models::KinematicModel;

// Subclass of Integrator.
class SomeIntegrator : public Integrator {
 public:
  SomeIntegrator(DiffDriveModel& diffdrive_model)
      : Integrator(diffdrive_model) {}

  State Step(const State& state, const Input& input, double dt) const override {
    auto derivative = (input(0) + input(1)) * dt * state;
    return derivative;
  }
};

class IntegratorTest : public ::testing::Test {
 protected:
  IntegratorTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}
};

TEST_F(IntegratorTest, Step) {
  // Kinematic model to use.
  DiffDriveModel model{0.5, 2.};

  // Integrator.
  SomeIntegrator integrator{model};

  State state1(VectorXd::Zero(3), VectorXd::Zero(0));
  State state2({1, -2, 3}, {});

  Input input1({1., 2.});
  Input input2({-5., 3.});

  VectorXd expected_derivative1(3), expected_derivative2(3),
      expected_derivative3(3);
  expected_derivative1 << 0, 0, 0;
  expected_derivative2 << 3, -6, 9;
  expected_derivative3 << -0.2, 0.4, -0.6;

  // Checking if the integrated value has been computed as expected.
  ASSERT_TRUE(integrator.Step(state1, input1, 0.05)
                  .get_data()
                  .isApprox(expected_derivative1));
  ASSERT_TRUE(integrator.Step(state2, input1, 1.)
                  .get_data()
                  .isApprox(expected_derivative2));
  ASSERT_TRUE(integrator.Step(state2, input2, 0.1)
                  .get_data()
                  .isApprox(expected_derivative3));
}

TEST_F(IntegratorTest, Integrate) {
  // Kinematic model to use.
  DiffDriveModel model{0.5, 2.};

  // Integrator.
  SomeIntegrator integrator{model};

  // Testing trivial integration.
  auto initial_state = State({1., 2., 0.}, {3., 4.});

  // When the time is zero, we should obtain the same state
  State integrated_state =
      integrator.Integrate(initial_state, Input({1, 2}), 0, 0.5);
  ASSERT_TRUE(integrated_state == initial_state);

  // Integration for when time is a multiple of dt.
  integrated_state =
      integrator.Integrate(initial_state, Input({2., 3.}), 2., 0.5);
  ASSERT_TRUE(integrated_state == 39.0625 * initial_state);

  // Integration for when time is not a multiple of dt.
  integrated_state =
      integrator.Integrate(initial_state, Input({6., 4.}), 2., 0.3);
  ASSERT_TRUE(integrated_state == pow(3, 6) * 2 * initial_state);

  // Integration when dt is larger than the total time. In this case, it should
  // only be integrated over time and not dt.
  integrated_state =
      integrator.Integrate(initial_state, Input({6., 4.}), 0.2, 0.5);
  ASSERT_TRUE(integrated_state == 2. * initial_state);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
