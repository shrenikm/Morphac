#include "gtest/gtest.h"

#include "math/geometry/include/lines.h"

namespace {

using std::numeric_limits;
using std::ostringstream;

using Eigen::Vector2d;

using morphac::common::aliases::Epsilon;
using morphac::common::aliases::Infinity;
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
  LineSpec line_spec1_{0, 0, 0};
  LineSpec line_spec2_{Infinity<double>, 0., 0};
  LineSpec line_spec3_{1, 0, 0};
  LineSpec line_spec4_{-1, 0, 0};
};

TEST_F(LinesTest, Equality) {
  LineSpec l1{1., 2., 3.};
  LineSpec l2{0.5 + 0.5, 7. - 5., 18. / 6.};
  LineSpec l3{Infinity<double>, 0., 0.};
  LineSpec l4{Infinity<double>, 1. - 1., 3. - 3.};

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

TEST_F(LinesTest, ComputeStandardLineSpec) {
  // Standard lines.
  ASSERT_TRUE(ComputeLineSpec(Vector2d(0., 0.), Vector2d(1., 0.)) ==
              line_spec1_);
  ASSERT_TRUE(ComputeLineSpec(Vector2d(-10., 0.), Vector2d(5., 0.)) ==
              line_spec1_);

  ASSERT_TRUE(ComputeLineSpec(Vector2d(0., 0.), Vector2d(0., 1.)) ==
              line_spec2_);
  ASSERT_TRUE(ComputeLineSpec(Vector2d(0., -10.), Vector2d(0., 5.)) ==
              line_spec2_);

  ASSERT_TRUE(ComputeLineSpec(Vector2d(0., 0.), Vector2d(1., 1.)) ==
              line_spec3_);
  ASSERT_TRUE(ComputeLineSpec(Vector2d(-10., -10.), Vector2d(5., 5.)) ==
              line_spec3_);

  ASSERT_TRUE(ComputeLineSpec(Vector2d(0., 0.), Vector2d(-1., 1.)) ==
              line_spec4_);
  ASSERT_TRUE(ComputeLineSpec(Vector2d(-10., 10.), Vector2d(5., -5.)) ==
              line_spec4_);
}

TEST_F(LinesTest, ComputeAxesLineSpec) {
  // Test the LineSpecs of lines that are parallel to the x and y axes.
  ASSERT_TRUE(ComputeLineSpec(Vector2d(0., 7.), Vector2d(1., 7.)) ==
              LineSpec(0., Infinity<double>, 7.));
  ASSERT_TRUE(ComputeLineSpec(Vector2d(-2., -7.), Vector2d(2., -7.)) ==
              LineSpec(0., Infinity<double>, -7.));

  ASSERT_TRUE(ComputeLineSpec(Vector2d(7., 0.), Vector2d(7., 1.)) ==
              LineSpec(Infinity<double>, 7., Infinity<double>));
  ASSERT_TRUE(ComputeLineSpec(Vector2d(-7., -2.), Vector2d(-7., 2.)) ==
              LineSpec(Infinity<double>, -7., Infinity<double>));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

