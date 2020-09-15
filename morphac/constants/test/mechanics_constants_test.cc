#include "constants/include/mechanics_constants.h"

#include "gtest/gtest.h"

namespace {

using morphac::constants::AckermannModelConstants;
using morphac::constants::DiffdriveModelConstants;
using morphac::constants::DubinModelConstants;
using morphac::constants::TricycleModelConstants;

class MechanicsConstantsTest : public ::testing::Test {
 protected:
  MechanicsConstantsTest() {}

  void SetUp() override {}
};

TEST_F(MechanicsConstantsTest, AckermannModelConstants) {
  // Test Map constants.
  ASSERT_EQ(AckermannModelConstants::DEFAULT_WHEEL_DIAMETER_SCALER, 0.25);
  ASSERT_EQ(AckermannModelConstants::DEFAULT_WHEEL_SIZE_RATIO, 3.);
  ASSERT_EQ(AckermannModelConstants::DEFAULT_WIDTH_BUFFER_SCALER, 0.25 / 3.);
  ASSERT_EQ(AckermannModelConstants::DEFAULT_WIDTH_BUFFER, 0.2);
  ASSERT_EQ(AckermannModelConstants::DEFAULT_LENGTH_BUFFER_SCALER, 0.25);
  ASSERT_EQ(AckermannModelConstants::DEFAULT_LENGTH_BUFFER, 0.2);
}

TEST_F(MechanicsConstantsTest, DiffdriveModelConstants) {
  // Test Map constants.
  ASSERT_EQ(DiffdriveModelConstants::DEFAULT_WHEEL_SIZE_RATIO, 3.);
  ASSERT_EQ(DiffdriveModelConstants::DEFAULT_RADIUS_BUFFER_SCALER, 0.25);
  ASSERT_EQ(DiffdriveModelConstants::DEFAULT_RADIUS_BUFFER, 0.);
}

TEST_F(MechanicsConstantsTest, DubinModelConstants) {
  // Test Map constants.
  ASSERT_EQ(DubinModelConstants::DEFAULT_BASE, 0.5);
  ASSERT_EQ(DubinModelConstants::DEFAULT_HEIGHT, 0.5);
}

TEST_F(MechanicsConstantsTest, TricycleModelConstants) {
  // Test Map constants.
  ASSERT_EQ(TricycleModelConstants::DEFAULT_FRONT_WHEEL_DIAMETER_SCALER, 0.3);
  ASSERT_EQ(TricycleModelConstants::DEFAULT_FRONT_WHEEL_SIZE_RATIO, 3.);
  ASSERT_EQ(TricycleModelConstants::DEFAULT_BACK_WHEEL_DIAMETER_SCALER, 0.2);
  ASSERT_EQ(TricycleModelConstants::DEFAULT_BACK_WHEEL_SIZE_RATIO, 3.);
  ASSERT_EQ(TricycleModelConstants::DEFAULT_WIDTH_BUFFER_SCALER, 0.2 / 3.);
  ASSERT_EQ(TricycleModelConstants::DEFAULT_WIDTH_BUFFER, 0.2);
  ASSERT_EQ(TricycleModelConstants::DEFAULT_LENGTH_BUFFER_SCALER, 0.25);
  ASSERT_EQ(TricycleModelConstants::DEFAULT_LENGTH_BUFFER, 0.2);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}