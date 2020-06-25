#include "simulation/include/playground.h"

namespace morphac {
namespace simulation {

using morphac::environments::Environment;
using morphac::math::numeric::Integrator;
using morphac::math::numeric::IntegratorType;
using morphac::robot::blueprint::Robot;
using morphac::robot::pilot::Pilot;
using morphac::utils::IntegratorFromType;
using morphac::mechanics::models::KinematicModel;

Playground::Playground(const PlaygroundSpec& spec,
                       const Environment& environment)
    : spec_(spec), playground_state_(environment) {}

const PlaygroundState& Playground::get_state() const {
    return playground_state_;
}

void Playground::AddRobot(const Robot& robot, const Pilot& pilot,
                          const IntegratorType& integrator_type) {
    // Making sure that the robot uid doesn't exist in any of the oracles.
    // UID uniqueness checking for the robot oracle happens through
    // PlaygroundState's AddRobot call.
    MORPH_REQUIRE(
        integrator_oracle_.find(robot.get_uid()) == integrator_oracle_.end(),
        std::logic_error,
        "Integrator with this UID already exists in the state.");
    MORPH_REQUIRE(pilot_oracle_.find(robot.get_uid()) == pilot_oracle_.end(),
                  std::logic_error,
                  "Pilot with this UID already exists in the state.");

    // Casting the unique ptr integrator to a non const reference.
    Integrator& integrator = *(IntegratorFromType(
        integrator_type,
        const_cast<KinematicModel&>(robot.get_kinematic_model())));

    // Updating the oracles.
    playground_state_.AddRobot(robot);
    integrator_oracle_.insert({robot.get_uid(), integrator});
    pilot_oracle_.insert({robot.get_uid(), const_cast<Pilot&>(pilot)});
}

}  // namespace simulation
}  // namespace morphac
