#ifndef PLAYGROUND_SPEC_H
#define PLAYGROUND_SPEC_H

namespace morphac {
namespace simulation {

struct PlaygroundSpec {
  std::string name;
  double dt;

  int gui_width;
  int gui_height;
};

}  // namespace simulation
}  // namespace morphac

#endif
