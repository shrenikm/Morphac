#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "third_party/Eigen/Dense"

namespace morphac {
namespace environments {

class Environment {

  public:
    Environment(int width, int height);

  private:
    int width_;
    int height_;
};

} // namespace environments
} // namespace morphac

#endif

