#ifndef DUBIN_MODEL_H
#define DUBIN_MODEL_H

#include "Eigen/Dense"

#include "mechanics/models/include/kinematic_model.h"

namespace morphac {
namespace mechanics {
namespace models {

class DubinModel : public morphac::mechanics::models::KinematicModel {
 public:
  DubinModel(const std::string name, const double speed);

  const double speed;
};

}  // namespace models
}  // namespace constructs
}  // namespace morphac

#endif

