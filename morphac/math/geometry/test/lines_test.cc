#include "gtest/gtest.h"

#include "math/geometry/include/line.h"

namespace {

using morphac::math::geometry::ComputeLineSpec;
using morphac::math::geometry::AreLinesParallel;
using morphac::math::geometry::AreLinesPerpendicular;

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

