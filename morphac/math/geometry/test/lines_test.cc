#include "math/geometry/include/lines.h"

#include "gtest/gtest.h"
#include "utils/include/numeric_utils.h"

namespace {

using std::atan2;
using std::isinf;
using std::numeric_limits;
using std::ostringstream;
using std::sqrt;
using std::tan;

using morphac::common::aliases::Epsilon;
using morphac::common::aliases::Infinity;
using morphac::common::aliases::Point;
using morphac::math::geometry::AreLinesParallel;
using morphac::math::geometry::AreLinesPerpendicular;
using morphac::math::geometry::ComputeLineSpec;
using morphac::math::geometry::ComputePointProjection;
using morphac::math::geometry::LineSpec;
using morphac::math::geometry::PointProjection;
using morphac::utils::IsEqual;

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

  // Some standard point projections.
  PointProjection point_projection1_{0., 0., Point(0., 0.)};
  PointProjection point_projection2_{2., Infinity<double>, Point(1., 1.)};
  PointProjection point_projection3_{10., Point(1., 1.)};
};

TEST_F(LinesTest, LineSpecEquality) {
  LineSpec l1{1., 2., 3.};
  LineSpec l2{0.5 + 0.5, 7. - 5., 18. / 6.};
  LineSpec l3{Infinity<double>, 0., 0.};
  LineSpec l4{Infinity<double>, 1. - 1., 3. - 3.};

  ASSERT_TRUE(l1 == l2);
  ASSERT_TRUE(l3 == l4);

  // Inequality.
  ASSERT_TRUE(l1 != LineSpec(1., 2., 3. + 1e-6));
  ASSERT_TRUE(l2 != LineSpec(1e25, 0., 0.));
}

TEST_F(LinesTest, LineSpecStringRepresentation) {
  // Testing that the << operator is overloaded properly.
  // We don't test the actual string representation.
  ostringstream os;
  os << line_spec1_;

  // Multiple pose object representations in the stream.
  os << " " << line_spec2_ << std::endl;
}

TEST_F(LinesTest, InvalidLineSpec) {
  // The Line specification is invalid iff both the intercepts are infinity.
  ASSERT_THROW(LineSpec(0., Infinity<double>, Infinity<double>),
               std::invalid_argument);
  // If any of the intercpets equal infinity, the slope must take specific
  // values (0./infinity).
  ASSERT_THROW(LineSpec(1., Infinity<double>, 0.), std::invalid_argument);
  ASSERT_THROW(LineSpec(Infinity<double>, Infinity<double>, 0.),
               std::invalid_argument);
  ASSERT_THROW(LineSpec(0., 0., Infinity<double>), std::invalid_argument);
  ASSERT_THROW(LineSpec(1., 0., Infinity<double>), std::invalid_argument);
}

TEST_F(LinesTest, PointProjection) {
  ASSERT_EQ(point_projection1_.distance, 0.);
  ASSERT_EQ(point_projection1_.alpha, 0.);
  ASSERT_TRUE(point_projection1_.projection.isApprox(Point(0., 0.)));
  ASSERT_TRUE(isinf(point_projection2_.alpha));
  ASSERT_TRUE(isinf(point_projection3_.alpha));
}

TEST_F(LinesTest, InvalidPointProjection) {
  // The distance cannot be negative.
  ASSERT_THROW(PointProjection(-0.1, 0., Point(0., 0.)), std::invalid_argument);
  ASSERT_THROW(PointProjection(-0.1, Point(0., 0.)), std::invalid_argument);
}

TEST_F(LinesTest, ComputeStandardLineSpec) {
  // Standard lines.
  ASSERT_TRUE(ComputeLineSpec(Point(0., 0.), Point(1., 0.)) == line_spec1_);
  ASSERT_TRUE(ComputeLineSpec(Point(-10., 0.), Point(5., 0.)) == line_spec1_);

  ASSERT_TRUE(ComputeLineSpec(Point(0., 0.), Point(0., 1.)) == line_spec2_);
  ASSERT_TRUE(ComputeLineSpec(Point(0., -10.), Point(0., 5.)) == line_spec2_);

  ASSERT_TRUE(ComputeLineSpec(Point(0., 0.), Point(1., 1.)) == line_spec3_);
  ASSERT_TRUE(ComputeLineSpec(Point(-10., -10.), Point(5., 5.)) == line_spec3_);

  ASSERT_TRUE(ComputeLineSpec(Point(0., 0.), Point(-1., 1.)) == line_spec4_);
  ASSERT_TRUE(ComputeLineSpec(Point(-10., 10.), Point(5., -5.)) == line_spec4_);
}

TEST_F(LinesTest, ComputeAxesLineSpec) {
  // Test the LineSpecs of lines that are parallel to the x and y axes.
  ASSERT_TRUE(ComputeLineSpec(Point(0., 7.), Point(1., 7.)) ==
              LineSpec(0., Infinity<double>, 7.));
  ASSERT_TRUE(ComputeLineSpec(Point(-2., -7.), Point(2., -7.)) ==
              LineSpec(0., Infinity<double>, -7.));

  ASSERT_TRUE(ComputeLineSpec(Point(7., 0.), Point(7., 1.)) ==
              LineSpec(Infinity<double>, 7., Infinity<double>));
  ASSERT_TRUE(ComputeLineSpec(Point(-7., -2.), Point(-7., 2.)) ==
              LineSpec(Infinity<double>, -7., Infinity<double>));
}

TEST_F(LinesTest, ComputeCustomLineSpec) {
  // Tests LineSpecs of custom lines.
  ASSERT_TRUE(ComputeLineSpec(Point(0., 2.), Point(5., 7.)) ==
              LineSpec(1., -2., 2.));
  ASSERT_TRUE(ComputeLineSpec(Point(-3., 0.), Point(-8., 5.)) ==
              LineSpec(-1., -3., -3.));

  ASSERT_TRUE(ComputeLineSpec(Point(9., 0.), Point(0., 3.)) ==
              LineSpec(tan(M_PI - atan2(3., 9.)), 9., 3.));
  ASSERT_TRUE(ComputeLineSpec(Point(-12., 0.), Point(0., 21.)) ==
              LineSpec(21. / 12., -12., 21.));
}

TEST_F(LinesTest, AreLinesParallel) {
  // We don't test the LineSpec overload as that gets called internally anyway.
  ASSERT_TRUE(AreLinesParallel(Point(0., 0.), Point(1., 0.), Point(-5., 0.),
                               Point(-2., 0.)));
  ASSERT_TRUE(AreLinesParallel(Point(0., 0.), Point(1., 0.), Point(-2., 10.),
                               Point(2., 10.)));

  ASSERT_TRUE(AreLinesParallel(Point(0., 0.), Point(0., 1.), Point(0., 10.),
                               Point(0., 20.)));
  ASSERT_TRUE(AreLinesParallel(Point(0., 0.), Point(0., 1.), Point(-10., -2.),
                               Point(-10, 2.)));

  ASSERT_TRUE(AreLinesParallel(Point(0., 0.), Point(1., 1.), Point(2., 2.),
                               Point(4., 4.)));
  ASSERT_TRUE(AreLinesParallel(Point(0., 0.), Point(1., 1.), Point(-5., 0.),
                               Point(15., 20.)));

  ASSERT_TRUE(AreLinesParallel(Point(0., 0.), Point(-1., 1.), Point(-2., 2.),
                               Point(4., -4.)));
  ASSERT_TRUE(AreLinesParallel(Point(0., 0.), Point(-1., 1.), Point(-5., 0.),
                               Point(15., -20.)));
}

TEST_F(LinesTest, AreLinesPerpendicular) {
  // We don't test the LineSpec overload as that gets called internally anyway.
  ASSERT_TRUE(AreLinesPerpendicular(Point(0., 0.), Point(1., 0.), Point(0., 0.),
                                    Point(0., 1.)));
  ASSERT_TRUE(AreLinesPerpendicular(Point(0., 0.), Point(1., 1.), Point(0., 0.),
                                    Point(-1., 1.)));

  ASSERT_TRUE(AreLinesPerpendicular(Point(0., 0.), Point(1., 0.),
                                    Point(10., -2.), Point(10., 2.)));
  ASSERT_TRUE(AreLinesPerpendicular(Point(0., 0.), Point(0., 1.),
                                    Point(-2., 10.), Point(2., 10.)));

  ASSERT_TRUE(AreLinesPerpendicular(Point(0., 0.), Point(1., 1.),
                                    Point(-10., 15.), Point(2., 3.)));
  ASSERT_TRUE(AreLinesPerpendicular(Point(0., 0.), Point(-1., 1.),
                                    Point(-23., -20.), Point(-1., 2.)));
}

TEST_F(LinesTest, ComputePointProjectionSegment) {
  // Test project computation to a line segment.
  // Defining three segments for testing.
  Point start_point1(0., 0.), end_point1(1., 0.);
  Point start_point2(0., 3.), end_point2(0., -2.);
  Point start_point3(-1., -1.), end_point3(4., 4.);

  // Testing different projections for these three segments.
  PointProjection point_projection1 =
      ComputePointProjection(Point(-1., 0.), start_point1, end_point1);
  ASSERT_EQ(point_projection1.alpha, -1.);
  ASSERT_EQ(point_projection1.distance, 0.);
  ASSERT_TRUE(point_projection1.projection.isApprox(Point(-1., 0.)));

  PointProjection point_projection2 =
      ComputePointProjection(Point(5., 5.), start_point1, end_point1);
  ASSERT_EQ(point_projection2.alpha, 5.);
  ASSERT_EQ(point_projection2.distance, 5.);
  ASSERT_TRUE(point_projection2.projection.isApprox(Point(5., 0.)));

  PointProjection point_projection3 =
      ComputePointProjection(Point(0.1, 0.), start_point1, end_point1);
  ASSERT_EQ(point_projection3.alpha, 0.1);
  ASSERT_EQ(point_projection3.distance, 0.);
  ASSERT_TRUE(point_projection3.projection.isApprox(Point(0.1, 0.)));

  PointProjection point_projection4 =
      ComputePointProjection(Point(0, 4.), start_point2, end_point2);
  ASSERT_EQ(point_projection4.alpha, -0.2);
  ASSERT_EQ(point_projection4.distance, 0.);
  ASSERT_TRUE(point_projection4.projection.isApprox(Point(0., 4.)));

  PointProjection point_projection5 =
      ComputePointProjection(Point(-2, -7.), start_point2, end_point2);
  ASSERT_EQ(point_projection5.alpha, 2.);
  ASSERT_EQ(point_projection5.distance, 2.);
  ASSERT_TRUE(point_projection5.projection.isApprox(Point(0., -7.)));

  PointProjection point_projection6 =
      ComputePointProjection(Point(0., 0.), start_point2, end_point2);
  ASSERT_EQ(point_projection6.alpha, 0.6);
  ASSERT_EQ(point_projection6.distance, 0.);
  ASSERT_TRUE(point_projection6.projection.isApprox(Point(0., 0.)));

  PointProjection point_projection7 =
      ComputePointProjection(Point(-6., -6.), start_point3, end_point3);
  ASSERT_EQ(point_projection7.alpha, -1.);
  ASSERT_EQ(point_projection7.distance, 0.);
  ASSERT_TRUE(point_projection7.projection.isApprox(Point(-6., -6.)));

  PointProjection point_projection8 =
      ComputePointProjection(Point(0., 10.), start_point3, end_point3);
  ASSERT_EQ(point_projection8.alpha, 1.2);
  // Using IsEqual, because of the distance float errors.
  ASSERT_TRUE(IsEqual(point_projection8.distance, sqrt(50.), 1e-9));
  ASSERT_TRUE(point_projection8.projection.isApprox(Point(5., 5.)));

  PointProjection point_projection9 =
      ComputePointProjection(Point(0., 0.), start_point3, end_point3);
  ASSERT_EQ(point_projection9.alpha, 0.2);
  ASSERT_EQ(point_projection9.distance, 0.);
  ASSERT_TRUE(point_projection9.projection.isApprox(Point(0., 0.)));
}

TEST_F(LinesTest, ComputePointProjectionLineParam) {
  // Test project computation to a line.
  // Defining three line specs for testing.
  LineSpec line_spec1{0., Infinity<double>, 0.};
  LineSpec line_spec2{Infinity<double>, 0., Infinity<double>};
  LineSpec line_spec3{1., 0., 0.};

  // Testing different projections for these three segments.
  PointProjection point_projection1 =
      ComputePointProjection(Point(5., 5.), line_spec1);
  ASSERT_EQ(point_projection1.alpha, Infinity<double>);
  ASSERT_EQ(point_projection1.distance, 5.);
  ASSERT_TRUE(point_projection1.projection.isApprox(Point(5., 0.)));

  PointProjection point_projection2 =
      ComputePointProjection(Point(-3., 0.), line_spec1);
  ASSERT_EQ(point_projection2.alpha, Infinity<double>);
  ASSERT_EQ(point_projection2.distance, 0.);
  ASSERT_TRUE(point_projection2.projection.isApprox(Point(-3., 0.)));

  PointProjection point_projection3 =
      ComputePointProjection(Point(-10., 9.), line_spec2);
  ASSERT_EQ(point_projection3.alpha, Infinity<double>);
  ASSERT_EQ(point_projection3.distance, 10.);
  ASSERT_TRUE(point_projection3.projection.isApprox(Point(0., 9.)));

  PointProjection point_projection4 =
      ComputePointProjection(Point(0., -2.), line_spec2);
  ASSERT_EQ(point_projection4.alpha, Infinity<double>);
  ASSERT_EQ(point_projection4.distance, 0.);
  ASSERT_TRUE(point_projection4.projection.isApprox(Point(0., -2.)));

  PointProjection point_projection5 =
      ComputePointProjection(Point(0., 10.), line_spec3);
  ASSERT_EQ(point_projection5.alpha, Infinity<double>);
  // Using IsEqual, because of the distance float errors.
  ASSERT_TRUE(IsEqual(point_projection5.distance, sqrt(50.), 1e-9));
  ASSERT_TRUE(point_projection5.projection.isApprox(Point(5., 5.)));

  PointProjection point_projection6 =
      ComputePointProjection(Point(0., 0.), line_spec3);
  ASSERT_EQ(point_projection6.alpha, Infinity<double>);
  ASSERT_EQ(point_projection6.distance, 0.);
  ASSERT_TRUE(point_projection6.projection.isApprox(Point(0., 0.)));
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
