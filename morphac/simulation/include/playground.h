#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "environments/include/environment2D.h"

namespace morphac {
namespace simulation {

struct PlaygroundSpec {
  std::string name;
  double dt;

  int gui_width;
  int gui_height;
};

class Playground {
 public:
  Playground(const PlaygroundSpec& spec,
             const morphac::environments::Environment2D& environment2D);

  // Delete copy constructor.
  Playground(const Playground& playground) = delete;

  // Delete copy assignment.
  Playground& operator=(const Playground& playground) = delete;

 private:
  const PlaygroundSpec spec_;
  morphac::environments::Environment2D environment2D_;
};

}  // namespace simulation
}  // namespace morphac

#endif
