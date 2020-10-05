#include "environment/include/map.h"

#include "Eigen/Dense"
#include "gtest/gtest.h"

namespace {

using std::make_unique;
using std::unique_ptr;

using morphac::common::aliases::MapData;
using morphac::environment::Map;

class MapTest : public ::testing::Test {
 protected:
  MapTest() {
    // Set random seed for Eigen.
    srand(7);
    map1_ = make_unique<Map>(10, 10, 0.01);
    map2_ = make_unique<Map>(MapData::Random(500, 500), 0.01);
  }

  void SetUp() override {}

  unique_ptr<Map> map1_, map2_;
};

TEST_F(MapTest, CopyConstruction) {
  Map map1(*map1_);

  Map map2(20, 30, 0.1);
  Map map3(map2);

  ASSERT_EQ(map3.get_width(), 20);
  ASSERT_EQ(map3.get_height(), 30);
  ASSERT_EQ(map3.get_resolution(), 0.1);
}

TEST_F(MapTest, CopyAssignment) {
  Map map1 = *map1_;

  Map map2(20, 30, 0.1);
  Map map3 = map2;

  ASSERT_EQ(map3.get_width(), 20);
  ASSERT_EQ(map3.get_height(), 30);
  ASSERT_EQ(map3.get_resolution(), 0.1);
}

TEST_F(MapTest, InvalidConstruction) {
  ASSERT_THROW(Map(-1, -2, 0.01), std::invalid_argument);
  ASSERT_THROW(Map(1, 0, 0.01), std::invalid_argument);
  ASSERT_THROW(Map(0, 2, 0.01), std::invalid_argument);
  ASSERT_THROW(Map(1, 2, -0.01), std::invalid_argument);

  ASSERT_THROW(Map(MapData::Random(0, 100), 0.01), std::invalid_argument);
  ASSERT_THROW(Map(MapData::Random(100, 0), 0.01), std::invalid_argument);
  ASSERT_THROW(Map(MapData::Random(0, 0), 0.01), std::invalid_argument);
  ASSERT_THROW(Map(MapData::Random(200, 100), -0.01), std::invalid_argument);

  // Constructing with an invalid resolution.
  ASSERT_THROW(Map(10, 9.4, 0.123), std::invalid_argument);
  ASSERT_THROW(Map(10, 9.12, 0.0489), std::invalid_argument);
  // While creating the map with a data, the resolution is always right
  // as the width and height are computed from the data and resolution and the
  // data is always valid dimension wise. Hence we don't test it.
}

TEST_F(MapTest, Accessors) {
  Map map1{10, 9.5, 0.01};
  MapData data = MapData::Random(480, 640);
  Map map2{data, 0.02};

  ASSERT_EQ(map1.get_width(), 10);
  ASSERT_EQ(map1.get_height(), 9.5);
  ASSERT_EQ(map1.get_resolution(), 0.01);
  ASSERT_TRUE(map1.get_data().isApprox(MapData::Zero(950, 1000)));

  ASSERT_EQ(map2.get_width(), 12.8);
  ASSERT_EQ(map2.get_height(), 9.6);
  ASSERT_EQ(map2.get_resolution(), 0.02);
  ASSERT_TRUE(map2.get_data().isApprox(data));

  // Setting a different data.
  // Testing the get_data_ref.
  data = MapData::Random(480, 640);
  map2.get_data_ref() = data;

  ASSERT_EQ(map2.get_width(), 12.8);
  ASSERT_EQ(map2.get_height(), 9.6);
  ASSERT_EQ(map2.get_resolution(), 0.02);
  ASSERT_TRUE(map2.get_data().isApprox(data));

  // Also test the set_data function.
  data = 7 * MapData::Ones(480, 640);
  map2.set_data(data);

  ASSERT_EQ(map2.get_width(), 12.8);
  ASSERT_EQ(map2.get_height(), 9.6);
  ASSERT_EQ(map2.get_resolution(), 0.02);
  ASSERT_TRUE(map2.get_data().isApprox(data));
}

TEST_F(MapTest, Evolve) {
  Map new_map = map2_->Evolve(MapData::Ones(500, 500));

  ASSERT_EQ(new_map.get_width(), map2_->get_width());
  ASSERT_EQ(new_map.get_height(), map2_->get_height());
  ASSERT_EQ(new_map.get_resolution(), map2_->get_resolution());
  ASSERT_TRUE(new_map.get_data().isApprox(MapData::Ones(500, 500)));
}

TEST_F(MapTest, InvalidEvolve) {
  ASSERT_THROW(map2_->Evolve(MapData::Ones(499, 500)), std::invalid_argument);
  ASSERT_THROW(map2_->Evolve(MapData::Ones(500, 499)), std::invalid_argument);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
