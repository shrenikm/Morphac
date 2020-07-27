#ifndef PLANNER_H
#define PLANNER_H

namespace morphac {
namespace planners {
namespace base {

class Planner {
  public:
    Planner();
    virtual ~Planner() = 0;

    // The convention is to have a 'Compute' function in the derived class that
    // computes and returns a Trajectory or ControlInput object.
};

} // namespace base
} // namespace planners
} // namespace morphac

#endif
