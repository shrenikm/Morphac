#include "simulation/include/playground.h"

namespace morphac {
namespace simulation {

using morphac::environments::Environment;

Playground::Playground(const PlaygroundSpec& spec,
                       const Environment& environment)
    : spec_(spec), environment_(environment) {}

}  // namespace simulation
}  // namespace morphac
