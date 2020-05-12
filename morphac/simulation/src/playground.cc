#include "simulation/include/playground.h"

namespace morphac {
namespace simulation {

using morphac::environments::Environment2D;

Playground::Playground(const PlaygroundSpec& spec,
                       const Environment2D& environment2D)
    : spec_(spec), environment2D_(environment2D) {}

}  // namespace simulation
}  // namespace morphac
