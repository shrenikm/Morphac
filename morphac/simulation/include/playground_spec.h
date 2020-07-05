#ifndef PLAYGROUND_SPEC_H
#define PLAYGROUND_SPEC_H

#include <string>

namespace morphac {
namespace simulation {

struct PlaygroundSpec {
  const std::string name;
  const double dt;

  const int gui_width;
  const int gui_height;
};

}  // namespace simulation
}  // namespace morphac

#endif
