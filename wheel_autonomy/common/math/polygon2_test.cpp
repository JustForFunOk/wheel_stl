#include "wheel_autonomy/common/math/polygon2.h"

#include <gtest/gtest.h>

using namespace wheel_autonomy::common::math;

TEST(Polygon2, Constructor) {
  Polygon2d plg;
  plg.points = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}};

  EXPECT_EQ(5, plg.points.size());
}