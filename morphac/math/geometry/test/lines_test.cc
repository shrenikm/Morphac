#include "gtest/gtest.h"

#include "math/geometry/include/lines.h"

namespace {

using std::numeric_limits;
using std::ostringstream;

using morphac::math::geometry::ComputeLineSpec;
using morphac::math::geometry::LineSpec;
using morphac::math::geometry::AreLinesParallel;
using morphac::math::geometry::AreLinesPerpendicular;

class LinesTest : public ::testing::Test {
 protected:
  LinesTest() {
    // Set random seed for Eigen.
    srand(7);
  }

  void SetUp() override {}

  // Some standard lines defined by LineSpec.
  LineSpec line_spec1_{1, 0, 0, numeric_limits<double>::infinity()};
  LineSpec line_spec2_{0, 1, 0, 0};
  LineSpec line_spec3_{1, 1, 0, 0};
  LineSpec line_spec4_{-1, 1, 0, 0};
};

TEST_F(LinesTest, Equality) {
  LineSpec l1{1., 2., 3., 0.};
  LineSpec l2{0.5 + 0.5, 7. - 5., 18. / 6., 0.};
  LineSpec l3{0., 0., 0., numeric_limits<double>::infinity()};
  LineSpec l4{1. - 1., 0., 0., numeric_limits<double>::infinity()};

  ASSERT_TRUE(l1 == l2);
  ASSERT_TRUE(l3 == l4);
}

TEST_F(LinesTest, StringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << line_spec1_;

  // Multiple pose object representations in the stream.
  os << " " << line_spec2_ << std::endl;
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

