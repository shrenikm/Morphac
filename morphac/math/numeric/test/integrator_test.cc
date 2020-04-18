#include "Eigen/Dense"
#include "gtest/gtest.h"

#include "math/numeric/include/integrator.h"
#include "mechanics/models/include/diffdrive_model.h"

namespace {

using std::srand;

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

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
