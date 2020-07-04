#include "simulation/include/playground.h"

namespace morphac {
namespace simulation {

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::environment::Map;
using morphac::math::numeric::Integrator;
using morphac::math::numeric::IntegratorType;
using morphac::robot::blueprint::Robot;
using morphac::robot::driver::Pilot;
using morphac::utils::IntegratorFromType;
using morphac::mechanics::models::KinematicModel;

Playground::Playground(const PlaygroundSpec& spec,
                       const Map& map)
    : spec_(spec), playground_state_(map) {}

bool Playground::UidExistsInIntegratorOracle(const int uid) const {
    if (integrator_oracle_.find(uid) == integrator_oracle_.end()) {
        // Given uid doesn't exist in the integrator oracle.
        return false;
    }
    return true;
}

bool Playground::UidExistsInPilotOracle(const int uid) const {
    if (pilot_oracle_.find(uid) == pilot_oracle_.end()) {
        // Given uid doesn't exist in the integrator oracle.
        return false;
    }
    return true;
}

const PlaygroundState& Playground::get_state() const {
    return playground_state_;
}

const Robot& Playground::get_robot(const int uid) const {
    // UID existence check happens within playground state.
    return playground_state_.get_robot(uid);
}

const State& Playground::get_robot_state(const int uid) const {
    // UID existence check happens within playground state.
    return playground_state_.get_robot_state(uid);
}

void Playground::set_robot_state(const State& state, const int uid) {
    // UID existence check happens within playground state.
    playground_state_.set_robot_state(state, uid);
}

void Playground::AddRobot(const Robot& robot, const Pilot& pilot,
                          const IntegratorType& integrator_type,
                          const int uid) {
    // Making sure that the robot uid doesn't exist in any of the oracles.
    MORPH_REQUIRE(
        (!UidExistsInIntegratorOracle(uid)) && (!UidExistsInPilotOracle(uid)),
        std::invalid_argument, "Given UID already exists.");

    // Casting the unique ptr integrator to a non const reference.
    Integrator& integrator = *(IntegratorFromType(
        integrator_type,
        const_cast<KinematicModel&>(robot.get_kinematic_model())));

    // Updating the oracles.
    playground_state_.AddRobot(robot, uid);
    integrator_oracle_.insert({uid, integrator});
    pilot_oracle_.insert({uid, const_cast<Pilot&>(pilot)});
}

void Playground::Execute() {
    for (auto pilot_element : pilot_oracle_) {
        int uid = pilot_element.first;

        auto input = pilot_element.second.Execute(playground_state_, uid);

        State updated_state = integrator_oracle_.find(uid)->second.Step(
            get_robot_state(uid), input, spec_.dt);

        set_robot_state(updated_state, uid);
    }
}

}  // namespace simulation
}  // namespace morphac
