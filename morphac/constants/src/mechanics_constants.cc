#include "constants/include/mechanics_constants.h"

namespace morphac {
namespace constants {

const double AckermannModelConstants::DEFAULT_WHEEL_DIAMETER_SCALER{0.25};
const double AckermannModelConstants::DEFAULT_WHEEL_SIZE_RATIO{3.};
const double AckermannModelConstants::DEFAULT_WIDTH_BUFFER_SCALER{
    AckermannModelConstants::DEFAULT_WHEEL_DIAMETER_SCALER /
    AckermannModelConstants::DEFAULT_WHEEL_SIZE_RATIO};
const double AckermannModelConstants::DEFAULT_WIDTH_BUFFER{0.2};
const double AckermannModelConstants::DEFAULT_LENGTH_BUFFER_SCALER{0.25};
const double AckermannModelConstants::DEFAULT_LENGTH_BUFFER{0.2};

const double DiffdriveModelConstants::DEFAULT_WHEEL_SIZE_RATIO{3.};
const double DiffdriveModelConstants::DEFAULT_WIDTH_BUFFER_SCALER{2.5};
const double DiffdriveModelConstants::DEFAULT_WIDTH_BUFFER{0.};

const double DubinModelConstants::DEFAULT_BASE{0.5};
const double DubinModelConstants::DEFAULT_HEIGHT{0.5};

const double TricycleModelConstants::DEFAULT_FRONT_WHEEL_DIAMETER_SCALER{0.3};
const double TricycleModelConstants::DEFAULT_FRONT_WHEEL_SIZE_RATIO{3.};
const double TricycleModelConstants::DEFAULT_BACK_WHEEL_DIAMETER_SCALER{0.2};
const double TricycleModelConstants::DEFAULT_BACK_WHEEL_SIZE_RATIO{3.};
const double TricycleModelConstants::DEFAULT_WIDTH_BUFFER_SCALER{
    TricycleModelConstants::DEFAULT_BACK_WHEEL_DIAMETER_SCALER /
    TricycleModelConstants::DEFAULT_BACK_WHEEL_SIZE_RATIO};
const double TricycleModelConstants::DEFAULT_WIDTH_BUFFER{0.2};
const double TricycleModelConstants::DEFAULT_LENGTH_BUFFER_SCALER{0.25};
const double TricycleModelConstants::DEFAULT_LENGTH_BUFFER{0.2};

}  // namespace constants
}  // namespace morphac
