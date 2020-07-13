#ifndef PLAYGROUND_SPEC_H
#define PLAYGROUND_SPEC_H

#include <string>

namespace morphac {
namespace simulation {
namespace playground {

struct PlaygroundSpec {
  const std::string name;
  const double dt;
};

}  // namespace playground
}  // namespace simulation
}  // namespace morphac

#endif
