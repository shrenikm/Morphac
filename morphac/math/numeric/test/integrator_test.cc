#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "math/numeric/include/integrator.h"
#include "mechanics/models/include/diffdrive_model.h"

namespace {

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
  IntegratorTest() {}

  void SetUp() override { srand(7); }
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
                  .get_state_vector()
                  .isApprox(expected_derivative1));
  ASSERT_TRUE(integrator.Step(state2, input1, 1.)
                  .get_state_vector()
                  .isApprox(expected_derivative2));
  ASSERT_TRUE(integrator.Step(state2, input2, 0.1)
                  .get_state_vector()
                  .isApprox(expected_derivative3));
}

TEST_F(IntegratorTest, Integrate) {
  // Kinematic model to use.
  DiffDriveModel model{0.5, 2.};

  // Integrator.
  SomeIntegrator integrator{model};

  // Testing trivial integration.

  // When the time is zero, we should obtain the same state
  State integrated_state =
      integrator.Integrate(State({1, 2, 0}, {}), Input({1, 2}), 0, 0.5);
  // TODO: State equality.
  //ASSERT_TRUE(integrated_state.get_state_vector()
  State state1(3, 0);
  State state2(3, 0);
  std::cout << (state1 == state2) << std::endl;

}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
