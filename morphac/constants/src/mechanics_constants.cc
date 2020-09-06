#include "constants/include/mechanics_constants.h"

namespace morphac {
namespace constants {

const double AckermannModelConstants::STANDARD_WHEEL_DIAMETER_SCALER{0.25};
const double AckermannModelConstants::STANDARD_WHEEL_SIZE_RATIO{3.};
const double AckermannModelConstants::STANDARD_WIDTH_BUFFER_SCALER{
    AckermannModelConstants::STANDARD_WHEEL_DIAMETER_SCALER /
    AckermannModelConstants::STANDARD_WHEEL_SIZE_RATIO};
const double AckermannModelConstants::STANDARD_WIDTH_BUFFER{0.2};
const double AckermannModelConstants::STANDARD_LENGTH_BUFFER_SCALER{0.25};
const double AckermannModelConstants::STANDARD_LENGTH_BUFFER{0.2};

const double DiffDriveModelConstants::STANDARD_WHEEL_SIZE_RATIO{3.};
const double DiffDriveModelConstants::STANDARD_WIDTH_BUFFER_SCALER{2.5};
const double DiffDriveModelConstants::STANDARD_WIDTH_BUFFER{0.};

const double DubinModelConstants::STANDARD_BASE{0.5};
const double DubinModelConstants::STANDARD_HEIGHT{0.5};

const double TricycleModelConstants::STANDARD_FRONT_WHEEL_DIAMETER_SCALER{0.3};
const double TricycleModelConstants::STANDARD_BACK_WHEEL_DIAMETER_SCALER{0.2};
const double TricycleModelConstants::STANDARD_FRONT_WHEEL_SIZE_RATIO{3.};
const double TricycleModelConstants::STANDARD_BACK_WHEEL_SIZE_RATIO{3.};
const double TricycleModelConstants::STANDARD_WIDTH_BUFFER_SCALER{
    TricycleModelConstants::STANDARD_BACK_WHEEL_DIAMETER_SCALER /
    TricycleModelConstants::STANDARD_BACK_WHEEL_SIZE_RATIO};
const double TricycleModelConstants::STANDARD_WIDTH_BUFFER{0.2};
const double TricycleModelConstants::STANDARD_LENGTH_BUFFER_SCALER{0.25};
const double TricycleModelConstants::STANDARD_LENGTH_BUFFER{0.2};

}  // namespace constants
}  // namespace morphac
