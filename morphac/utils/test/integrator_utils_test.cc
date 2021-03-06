#include "utils/include/integrator_utils.h"

#include "constructs/include/control_input.h"
#include "constructs/include/state.h"
#include "gtest/gtest.h"
#include "math/numeric/include/all_integrators.h"
#include "mechanics/models/include/diffdrive_model.h"

namespace {

using Eigen::VectorXd;
using morphac::constructs::ControlInput;
using morphac::constructs::State;
using morphac::math::numeric::EulerIntegrator;
using morphac::math::numeric::Integrator;
using morphac::math::numeric::IntegratorType;
using morphac::math::numeric::MidPointIntegrator;
using morphac::math::numeric::RK4Integrator;
using morphac::mechanics::models::DiffdriveModel;
using morphac::utils::IntegratorFromType;

TEST(IntegratorUtilsTest, Construction) {
  // Test the construction for different types. Make sure the right integrator
  // is constructed for the given type.
  // Also check to make sure that the integrator is usable.
  DiffdriveModel model{1., 1.};
  auto integrator = IntegratorFromType(IntegratorType::kEulerIntegrator, model);
  ASSERT_TRUE(dynamic_cast<EulerIntegrator*>(integrator.get()) != nullptr);
  State integrated_state = integrator->Step(State(3, 0), ControlInput(2), 0.05);
  ASSERT_TRUE(integrated_state.get_data().isApprox(VectorXd::Zero(3)));

  integrator = IntegratorFromType(IntegratorType::kMidPointIntegrator, model);
  ASSERT_TRUE(dynamic_cast<MidPointIntegrator*>(integrator.get()) != nullptr);
  integrated_state = integrator->Step(State(3, 0), ControlInput(2), 0.05);
  ASSERT_TRUE(integrated_state.get_data().isApprox(VectorXd::Zero(3)));

  integrator = IntegratorFromType(IntegratorType::kRK4Integrator, model);
  ASSERT_TRUE(dynamic_cast<RK4Integrator*>(integrator.get()) != nullptr);
  integrated_state = integrator->Step(State(3, 0), ControlInput(2), 0.05);
  ASSERT_TRUE(integrated_state.get_data().isApprox(VectorXd::Zero(3)));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
