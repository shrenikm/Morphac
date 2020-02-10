#include "robot/blueprint/include/robot2D.h"

namespace morphac {
namespace robot {
namespace blueprint {


Robot2DParams::Robot2DParams(
    const string robot_name,
    const unordered_map<std::string, double> robot_params)
    : robot_name(robot_name), robot_params(robot_params) {}

}  // namespace models
}  // namespace robot
}  // namespace morphac


