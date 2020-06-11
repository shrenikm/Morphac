#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "environments/include/environment.h"

namespace morphac {
namespace simulation {

struct PlaygroundSpec {
  std::string name;
  double dt;

  int gui_width;
  int gui_height;
};

// class PlaygroundState {
// public:
//  PlaygroundState(const morphac::environments::Environment& environment);
//
//  // Delete copy constructor. We don't want to copy the state to avoid
//  incurring
//  // the cost of copying the environment object.
//  PlaygroundState(const PlaygroundState& playground_state) = delete;
//
//  // Also deleting copy assignment.
//  PlaygroundState& operator=(const PlaygroundState& playground_state) =
//  delete;
//
// private:
//  morphac::environments::Environment environment_;
//  std::unordered_map<string, morphac::robot::blueprint::Robot>
//  robot_oracle_;
//};

class Playground {
 public:
  Playground(const PlaygroundSpec& spec,
             const morphac::environments::Environment& environment);

  // Delete copy constructor.
  Playground(const Playground& playground) = delete;

  // Delete copy assignment.
  Playground& operator=(const Playground& playground) = delete;

 private:
  const PlaygroundSpec spec_;
  morphac::environments::Environment environment_;
};

}  // namespace simulation
}  // namespace morphac

#endif
