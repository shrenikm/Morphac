#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <unordered_map>

#include "environments/include/environment.h"
#include "math/numeric/include/integrator.h"
#include "robot/blueprint/include/robot.h"
#include "simulation/include/playground_state.h"

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
             const morphac::environments::Environment& environment);

  // Delete copy constructor.
  Playground(const Playground& playground) = delete;

  // Delete copy assignment.
  Playground& operator=(const Playground& playground) = delete;

  const PlaygroundState& get_state() const;

 private:
  const PlaygroundSpec spec_;
  PlaygroundState playground_state_;
  std::unordered_map<int, morphac::math::numeric::Integrator&>
      integrator_oracle_;
};

}  // namespace simulation
}  // namespace morphac

#endif
