#include "simulation/include/playground.h"

namespace morphac {
namespace simulation {


using morphac::environments::Environment;

Playground::Playground(const PlaygroundSpec& spec,
                       const Environment& environment)
    : spec_(spec), playground_state_(environment) {}

const PlaygroundState& Playground::get_state() const {
    return playground_state_;
}

}  // namespace simulation
}  // namespace morphac
