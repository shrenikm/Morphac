#ifndef CONTROLLER_H
#define CONTROLLER_H

namespace morphac {
namespace controllers {

class Controller {
  public:
    Controller();
    virtual ~Controller() = 0;

    // The convention is to have a 'Compute' function in the derived class that
    // computes and returns a ControlInput object.
};

} // namespace controllers
} // namespace morphac

#endif
