#ifndef MECHANICS_CONSTANTS_H
#define MECHANICS_CONSTANTS_H

namespace morphac {
namespace constants {

// Constants for the standard mechanics models footprints.
struct AckermannModelConstants {
  // Default footprint and visualization constants.

  // Standard wheel diameter as a multiple of the length.
  static const double DEFAULT_WHEEL_DIAMETER_SCALER;
  // Ratio of wheel diameter to thickness.
  static const double DEFAULT_WHEEL_SIZE_RATIO;
  // Percentage of the width that it has to be increased by for the footprint.
  static const double DEFAULT_WIDTH_BUFFER_SCALER;
  // Constant value that the width needs to be increased by for the footprint.
  static const double DEFAULT_WIDTH_BUFFER;
  // Percentage of the length that it has to be increased by for the footprint.
  static const double DEFAULT_LENGTH_BUFFER_SCALER;
  // Constant value that the length needs to be increased by for the footprint.
  static const double DEFAULT_LENGTH_BUFFER;
};

struct DiffdriveModelConstants {
  // Default footprint and visualization constants.

  // Ratio of wheel diameter to thickness.
  static const double DEFAULT_WHEEL_SIZE_RATIO;
  // Percentage of the width that it has to be increased by for the footprint.
  // It is called radius because at the end, it is added as a buffer to the
  // radius while creating the footprint.
  static const double DEFAULT_RADIUS_BUFFER_SCALER;
  // Constant value that the width needs to be increased by for the footprint.
  static const double DEFAULT_RADIUS_BUFFER;
};

struct DubinModelConstants {
  // Default footprint and visualization constants.

  // Default standard base length of the triangular footprint.
  static const double DEFAULT_BASE;
  // Default standard height of the triangular footprint.
  static const double DEFAULT_HEIGHT;
};

struct TricycleModelConstants {
  // Default footprint and visualization constants.

  // Standard front wheel diameter as a multiple of the length.
  static const double DEFAULT_FRONT_WHEEL_DIAMETER_SCALER;
  // Ratio of front wheel diameter to thickness.
  static const double DEFAULT_FRONT_WHEEL_SIZE_RATIO;
  // Standard back wheel diameter as a multiple of the length.
  static const double DEFAULT_BACK_WHEEL_DIAMETER_SCALER;
  // Ratio of back wheel diameter to thickness.
  static const double DEFAULT_BACK_WHEEL_SIZE_RATIO;
  // Percentage of the width that it has to be increased by for the footprint.
  static const double DEFAULT_WIDTH_BUFFER_SCALER;
  // Constant value that the width needs to be increased by for the footprint.
  static const double DEFAULT_WIDTH_BUFFER;
  // Percentage of the length that it has to be increased by for the footprint.
  static const double DEFAULT_LENGTH_BUFFER_SCALER;
  // Constant value that the length needs to be increased by for the footprint.
  static const double DEFAULT_LENGTH_BUFFER;
};

}  // namespace constants
}  // namespace morphac

#endif