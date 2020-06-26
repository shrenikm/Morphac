#include "simulation/include/playground.h"

namespace morphac {
namespace simulation {

using morphac::constructs::Input;
using morphac::constructs::State;
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

const Robot& Playground::get_robot(const int uid) const {
    auto robot_oracle = playground_state_.get_robot_oracle();

    // Make sure that a robot with the given uid exists in the oracle.
    MORPH_REQUIRE(robot_oracle.find(uid) != robot_oracle.end(),
                  std::invalid_argument,
                  "Robot with the given UID does not exist.");
    return playground_state_.get_robot_oracle()[uid]
}

const State& Playground::get_robot_state(const int uid) const {
    // We get the state after first getting the robot from the oracle. UID
    // checking takes place in the get_robot function.
    return get_robot(uid).get_state();
}

void Playground::set_robot_state(const int uid, const State& state) {
    // Make sure that a robot with the given uid exists in the oracle.
    MORPH_REQUIRE(playground_state_.get_robot_oracle().find(uid) !=
                      playground_state_.get_robot_oracle().end(),
                  std::invalid_argument,
                  "Robot with the given UID does not exist.");
    playground_state_.set_robot_state(uid, state);
}

void Playground::AddRobot(Robot& robot, Pilot& pilot,
                          const IntegratorType& integrator_type) {
    // Making sure that the robot uid doesn't exist in any of the oracles.
    // UID uniqueness checking for the robot oracle happens through
    // PlaygroundState's AddRobot call.
    int uid = robot.get_uid();
    MORPH_REQUIRE(integrator_oracle_.find(uid) == integrator_oracle_.end(),
                  std::logic_error,
                  "Integrator with this UID already exists in the state.");
    MORPH_REQUIRE(pilot_oracle_.find(uid) == pilot_oracle_.end(),
                  std::logic_error,
                  "Pilot with this UID already exists in the state.");
    // If the pilot UID has been initialized, it needs to be the same as
    // the robot UID. This isn't necessarily bad as the pilot UID gets
    // overwritten, but has a high likelihood of being a logical error and is
    // hence thrown as an exception.
    if (pilot.get_uid() >= 0) {
        MORPH_REQUIRE(uid == pilot.get_uid(), std::logic_error,
                      "Robot and Pilot UID do not match.");
    } else {
        // If the pilot UID has not been initialized, it is initialized with the
        // UID of the robot.
        pilot.set_uid(uid);
    }

    // Casting the unique ptr integrator to a non const reference.
    Integrator& integrator = *(IntegratorFromType(
        integrator_type,
        const_cast<KinematicModel&>(robot.get_kinematic_model())));

    // Updating the oracles.
    playground_state_.AddRobot(robot);
    integrator_oracle_.insert({uid, integrator});
    pilot_oracle_.insert({uid, const_cast<Pilot&>(pilot)});
}

void Playground::Execute() {
    for (auto pilot_element : pilot_oracle_) {
        // int uid = pilot_element.first;

        auto input = pilot_element.second.Execute(playground_state_);
    }
}

}  // namespace simulation
}  // namespace morphac
