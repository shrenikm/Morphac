#ifndef MECHANICS_CONSTANTS_H
#define MECHANICS_CONSTANTS_H

namespace morphac {
namespace constants {

// Constants for the standard mechanics models footprints.
struct AckermannModelConstants {
  // Default footprint and visualization constants.

  // Standard wheel diameter as a multiple of the length.
  static const double STANDARD_WHEEL_DIAMETER_SCALER;
  // Ratio of wheel diameter to thickness.
  static const double STANDARD_WHEEL_SIZE_RATIO;
  // Percentage of the width that it has to be increased by for the footprint.
  static const double STANDARD_WIDTH_BUFFER_SCALER;
  // Constant value that the width needs to be increased by for the footprint.
  static const double STANDARD_WIDTH_BUFFER;
  // Percentage of the length that it has to be increased by for the footprint.
  static const double STANDARD_LENGTH_BUFFER_SCALER;
  // Constant value that the length needs to be increased by for the footprint.
  static const double STANDARD_LENGTH_BUFFER;
};

struct DiffDriveModelConstants {
  // Default footprint and visualization constants.

  // Ratio of wheel diameter to thickness.
  static const double STANDARD_WHEEL_SIZE_RATIO;
  // Percentage of the width that it has to be increased by for the footprint.
  static const double STANDARD_WIDTH_BUFFER_SCALER;
  // Constant value that the width needs to be increased by for the footprint.
  static const double STANDARD_WIDTH_BUFFER;
};

struct DubinModelConstants {
  // Default footprint and visualization constants.

  // Default standard base length of the triangular footprint.
  static const double STANDARD_BASE;
  // Default standard height of the triangular footprint.
  static const double STANDARD_HEIGHT;
};

struct TricycleModelConstants {
  // Default footprint and visualization constants.

  // Standard front wheel diameter as a multiple of the length.
  static const double STANDARD_FRONT_WHEEL_DIAMETER_SCALER;
  // Ratio of front wheel diameter to thickness.
  static const double STANDARD_FRONT_WHEEL_SIZE_RATIO;
  // Standard back wheel diameter as a multiple of the length.
  static const double STANDARD_BACK_WHEEL_DIAMETER_SCALER;
  // Ratio of back wheel diameter to thickness.
  static const double STANDARD_BACK_WHEEL_SIZE_RATIO;
  // Percentage of the width that it has to be increased by for the footprint.
  static const double STANDARD_WIDTH_BUFFER_SCALER;
  // Constant value that the width needs to be increased by for the footprint.
  static const double STANDARD_WIDTH_BUFFER;
  // Percentage of the length that it has to be increased by for the footprint.
  static const double STANDARD_LENGTH_BUFFER_SCALER;
  // Constant value that the length needs to be increased by for the footprint.
  static const double STANDARD_LENGTH_BUFFER;
};

}  // namespace constants
}  // namespace morphac

#endif