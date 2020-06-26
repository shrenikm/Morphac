#ifndef PILOT_H
#define PILOT_H

#include "constructs/include/input.h"
#include "simulation/include/playground_state.h"

namespace morphac {
namespace robot {
namespace pilot {

class Pilot {
 public:
  Pilot(const int uid = -1);

  virtual morphac::constructs::Input Execute(
      const morphac::simulation::PlaygroundState& playground_state) const = 0;

  int get_uid() const;
  void set_uid(const int uid);

 private:
  int uid_;
};

}  // namespace pilot
}  // namespace robot
}  // namespace morphac

#endif
