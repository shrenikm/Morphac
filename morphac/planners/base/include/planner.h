#ifndef PLANNER_H
#define PLANNER_H

namespace morphac {
namespace planners {

class Planner {
  public:
    Planner();
    virtual ~Planner() = 0;

    // The convention is to have a 'Compute' function in the derived class that
    // computes and returns a Trajectory or ControlInput object.
};

} // namespace planners
} // namespace morphac

#endif
