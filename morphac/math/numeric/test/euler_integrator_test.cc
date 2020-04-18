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

// Subclass of KinematicModel to create a custom gradient function.
class CustomKinematicModel : public KinematicModel {
 public:
  CustomKinematicModel(int size_pose, int size_velocity, int size_input,
                       double a)
      : KinematicModel(size_pose, size_velocity, size_input), a(a) {}

  State ComputeStateDerivative(const State& state,
                               const Input& input) const override {
    // We define t * [(u1 + u2) * x + a]
    // dx/dt = (u1 + u2)*x + a
    State ones_state{VectorXd::Ones(size_pose), VectorXd::Ones(size_velocity)};
    auto derivative = (input(0) + input(1)) * state + a * ones_state;
    return derivative;
  }

  double a;
};

class EulerIntegratorTest : public ::testing::Test {
 protected:
  EulerIntegratorTest() {}

  void SetUp() override { srand(7); }
};

TEST_F(EulerIntegratorTest, DiffDriveModelStep) {
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

TEST_F(EulerIntegratorTest, CustomKinematicModelStep) {
  CustomKinematicModel custom_model{3, 2, 4, 10.};
  EulerIntegrator euler_integrator{custom_model};

  // Basic step computation test.
  State state(3, 2);
  Input input(4);
  auto derivative = euler_integrator.Step(state, input, 1);

  // For this case, only the 'a' component contributes to the derivative hence
  // the derivative must be a state of ones.
  ASSERT_TRUE(derivative.get_state_vector().isApprox(10 * VectorXd::Ones(5)));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
