#include "wheel_autonomy/common/math/rectangle2.h"

#include <gtest/gtest.h>

using namespace wheel_autonomy::common::math;

TEST(Rectangle2, Iou) {
  Rectangle2d rect({0.0, 0.0}, {1.0, 1.0});
  {
    Rectangle2d another_rect({2.0, 0.0}, {3.0, 1.0});
    double iou = rect.Iou(another_rect);
    EXPECT_FLOAT_EQ(0.0, iou);
  }
  {
    Rectangle2d another_rect({0.0, 0.0}, {1.0, 1.0});
    double iou = rect.Iou(another_rect);
    EXPECT_FLOAT_EQ(1.0, iou);
  }
  {
    Rectangle2d another_rect({0.5, 0.5}, {1.5, 1.5});
    double iou = rect.Iou(another_rect);
    EXPECT_FLOAT_EQ(1.0 / 7.0, iou);
  }
}