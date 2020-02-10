#ifndef ROBOT_PARAMS_H
#define ROBOT_PARAMS_H

#include <unordered_map>

#include "Eigen/Dense"

#include "constructs/include/pose.h"
#include "constructs/include/state.h"
#include "constructs/include/velocity.h"
#include "mechanics/include/kinematic_model.h"
#include "robot/blueprint/include/footprint2D.h"

namespace morphac {
namespace robot {
namespace blueprint {

struct Robot2DParams {
  Robot2DParams(const std::string robot_name,
                const std::unordered_map<std::string, double> robot_params);

  const std::string robot_name;
  const std::unordered_map<std::string, double> robot_params;
};

#endif


