#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Eigen/Dense"
#include "common/aliases/include/eigen_aliases.h"
#include "common/error_handling/include/error_macros.h"

namespace morphac {
namespace environment {

class Map {
 public:
  Map(const double width, const double height, const double resolution);
  Map(const morphac::common::aliases::MapData& data, const double resolution);

  double get_width() const;
  double get_height() const;
  double get_resolution() const;
  // Get data function for constant Map objects.
  const morphac::common::aliases::MapData& get_data() const;
  // Get data function for when the data needs to be changed.
  // This is what gets exposed in the python bindings so that we can do inplace
  // numpy operations like map.data[:10, :10] = 0
  morphac::common::aliases::MapData& get_data_ref();

  void set_data(const morphac::common::aliases::MapData& data);
  Map Evolve(const morphac::common::aliases::MapData& data);

 private:
  double width_;
  double height_;
  double resolution_;
  morphac::common::aliases::MapData data_;
};

}  // namespace environment
}  // namespace morphac

#endif
