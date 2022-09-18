#include <gtest/gtest.h>
#include "wheel_autonomy/common/math.h"

TEST(math, Vec2d) {
  wheelautonomy::Vec2d vec2d(1.0, 1.0);

  EXPECT_DOUBLE_EQ(1.0, vec2d.x);
  EXPECT_DOUBLE_EQ(1.0, vec2d.y);
}