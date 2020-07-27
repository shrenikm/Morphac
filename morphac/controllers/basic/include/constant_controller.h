#ifndef CONSTANT_CONTROLLER_H
#define CONSTANT_CONTROLLER_H

#include "constructs/include/control_input.h"
#include "controllers/base/include/controller.h"

namespace morphac {
namespace controllers {
namespace basic {

class ConstantController : public morphac::controllers::base::Controller {
 public:
  ConstantController(const Eigen::VectorXd& control_input_data);
  ~ConstantController() override;

  const morphac::constructs::ControlInput& Compute();

 private:
  morphac::constructs::ControlInput control_input_;
};

}  // namespace basic
}  // namespace controllers
}  // namespace morphac

#endif
