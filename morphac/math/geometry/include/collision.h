#ifndef COLLISION_H
#define COLLISION_H

#define _USE_MATH_DEFINES

#include <cmath>

#include "common/aliases/include/eigen_aliases.h"
#include "morphac/robot/blueprint/include/robot.h"

namespace morphac {
namespace math {
namespace geometry {

bool DoRobotsCollide(const morphac::robot::blueprint::Robot& robot1,
                     const morphac::robot::blueprint::Robot& robot2);

bool DoesRobotCollideWithPoint(const morphac::robot::blueprint::Robot& robot,
                               const morphac::common::aliases::Point& point);

}  // namespace geometry
}  // namespace math
}  // namespace morphac