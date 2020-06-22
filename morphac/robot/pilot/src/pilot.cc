#include "robot/pilot/include/pilot.h"

namespace morphac {
namespace robot {
namespace pilot {

Pilot::Pilot(const int uid) : uid_(uid) {
  MORPH_REQUIRE(uid >= 0, std::invalid_argument, "UID must be non-negative.");
}

int Pilot::get_uid() const { return uid_; }

void Pilot::set_uid(const int uid) {
  MORPH_REQUIRE(uid >= 0, std::invalid_argument, "UID must be non-negative.");
  uid_ = uid;
}

}  // namespace pilot
}  // namespace robot
}  // namespace morphac
