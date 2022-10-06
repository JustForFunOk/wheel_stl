#pragma once

#include "wheel_autonomy/common/math/line_segment2.h"

#include <gtest/gtest.h>

using namespace wheel_autonomy::common::math;

TEST(LineSegment2, Constructor) {
  Point2d start_pt(1.0, 1.0);
  Point2d end_pt(2.0, 2.0);
  LineSegment2d line_seg_a(start_pt, end_pt);

  LineSegment2d line_seg_b(1.0, 1.0, 2.0, 2.0);
}