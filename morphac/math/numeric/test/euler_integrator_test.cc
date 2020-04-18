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

// Subclass of KinematicModel to create a custom gradient function.
class SomeKinematicModel : public KinematicModel {
 public:
  SomeKinematicModel(int size_pose, int size_velocity, int size_input, double a)
      : KinematicModel(size_pose, size_velocity, size_input), a(a) {}

  State ComputeStateDerivative(const State& state,
                               const Input& input) const override {
    auto derivative = (input(0) + input(1)) * state + a;
    return derivative;
  }

  double a;
};

class EulerIntegratorTest : public ::testing::Test {
 protected:
  EulerIntegratorTest() {}

  void SetUp() override { srand(7); }
};

TEST_F(EulerIntegratorTest, Subclass) {
  // Kinematic models to use.
  DiffDriveModel model{0.5, 2.};

  // Integrator.
  SomeIntegrator integrator{model};

  State state1{VectorXd::Zero(3), VectorXd::Zero(0)};

  VectorXd state_vector2(3);
  state_vector2 << 1, -2, 3;
  State state2{state_vector2, VectorXd::Zero(0)};

  VectorXd input_vector1(2), input_vector2(2);
  input_vector1 << 1., 2.;
  input_vector2 << -5., 3.;
  Input input1{input_vector1};
  Input input2{input_vector2};

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

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
