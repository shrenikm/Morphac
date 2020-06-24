#include "simulation/include/playground.h"

namespace morphac {
namespace simulation {


using morphac::environments::Environment;
using morphac::math::numeric::IntegratorType;
using morphac::robot::blueprint::Robot;
using morphac::robot::pilot::Pilot;

Playground::Playground(const PlaygroundSpec& spec,
                       const Environment& environment)
    : spec_(spec), playground_state_(environment) {}

const PlaygroundState& Playground::get_state() const {
    return playground_state_;
}

//void Playground::AddRobot(const Robot& robot, const Pilot& pilot, const
//        IntegratorType& integrator_type) {
//}

}  // namespace simulation
}  // namespace morphac
