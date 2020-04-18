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

TEST_F(EulerIntegratorTest, DiffDriveStep) {
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

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
