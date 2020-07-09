#include "simulation/playground/include/playground.h"

namespace morphac {
namespace simulation {
namespace playground {

using morphac::constructs::Input;
using morphac::constructs::State;
using morphac::environment::Map;
using morphac::math::numeric::Integrator;
using morphac::math::numeric::EulerIntegrator;
using morphac::math::numeric::IntegratorType;
using morphac::robot::blueprint::Robot;
using morphac::robot::pilot::Pilot;
using morphac::utils::IntegratorFromType;
using morphac::mechanics::models::KinematicModel;

Playground::Playground(const PlaygroundSpec& spec, const Map& map)
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

PlaygroundState& Playground::get_state() { return playground_state_; }

const Pilot& Playground::get_pilot(const int uid) {
    // Making sure that the UID exists.
    MORPH_REQUIRE(UidExistsInPilotOracle(uid), std::invalid_argument,
                  "Given UID does not exist.");
    return pilot_oracle_.find(uid)->second;
}

const Integrator& Playground::get_integrator(const int uid) {
    // Making sure that the UID exists.
    MORPH_REQUIRE(UidExistsInIntegratorOracle(uid), std::invalid_argument,
                  "Given UID does not exist.");
    return *integrator_oracle_[uid];
}

void Playground::AddRobot(const Robot& robot, const Pilot& pilot,
                          const IntegratorType& integrator_type,
                          const int uid) {
    // Making sure that the robot uid doesn't exist in any of the oracles.
    MORPH_REQUIRE(
        (!UidExistsInPilotOracle(uid)) && (!UidExistsInIntegratorOracle(uid)),
        std::invalid_argument, "Given UID already exists.");

    // Also making sure that we have the same number of elements in each
    // of the oracles. This is just a sanity check done before adding the new
    // robot.
    MORPH_REQUIRE(
        (playground_state_.NumRobots() == (int)integrator_oracle_.size()) &&
            (integrator_oracle_.size() == pilot_oracle_.size()),
        std::logic_error,
        "Oracles are of different sizes. Something has gone wrong.");

    // Updating the oracles.
    playground_state_.AddRobot(robot, uid);
    integrator_oracle_[uid] = std::move(IntegratorFromType(
        integrator_type,
        const_cast<KinematicModel&>(robot.get_kinematic_model())));
    pilot_oracle_.insert({uid, const_cast<Pilot&>(pilot)});
}

void Playground::Execute() {
    for (std::pair<int, Pilot&> pilot_element : pilot_oracle_) {
        int uid = pilot_element.first;

        Input input = pilot_element.second.Execute(playground_state_, uid);

        // Also making sure that the input is of the correct dimensions.
        MORPH_REQUIRE(
            playground_state_.get_robot(uid).get_kinematic_model().input_size ==
                input.get_size(),
            std::logic_error,
            "Input computed by the pilot is of incorrect dimensions.");

        State updated_state = integrator_oracle_.find(uid)->second->Step(
            playground_state_.get_robot_state(uid), input, spec_.dt);

        playground_state_.set_robot_state(updated_state, uid);
    }
}

}  // namespace playground
}  // namespace simulation
}  // namespace morphac
