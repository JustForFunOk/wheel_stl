#include "wheel_autonomy/common/math/point2.h"

#include <gtest/gtest.h>

using namespace wheel_autonomy::common::math;

TEST(Point2, Constructor) {
  Point2d pt_a(1.0, 1.0);

  EXPECT_DOUBLE_EQ(1.0, pt_a.x);
  EXPECT_DOUBLE_EQ(1.0, pt_a.y);
}

// TEST(Point2, Inside) {
//   wheel_autonomy::Point2d pt(1.0, 1.0);

//   wheel_autonomy::Polygon2d plg;
//   plg.points = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}};

//   bool is_inside = pt.Inside(plg);

//   EXPECT_EQ(true, is_inside);
// }
