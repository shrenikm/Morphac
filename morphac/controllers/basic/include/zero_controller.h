#ifndef ZERO_CONTROLLER_H
#define ZERO_CONTROLLER_H

#include "constructs/include/control_input.h"
#include "controllers/base/include/controller.h"

namespace morphac {
namespace controllers {
namespace basic {

class ZeroController : public morphac::controllers::base::Controller {
 public:
  ZeroController(const int control_input_size);
  ~ZeroController() override;

  const morphac::constructs::ControlInput& Compute();

 private:
  morphac::constructs::ControlInput control_input_;
};

}  // namespace basic
}  // namespace controllers
}  // namespace morphac

#endif
