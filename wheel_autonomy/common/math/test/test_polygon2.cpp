#include "wheel_autonomy/common/math/polygon2.h"

#include <gtest/gtest.h>

using namespace wheel_autonomy::common::math;

TEST(Polygon2, Constructor) {
  Polygon2d plg;
  // plg.Points() = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}};

  // EXPECT_EQ(5, plg.Points().size());
}

// TEST(Point2, Inside) {
//   wheel_autonomy::Point2d pt(1.0, 1.0);

//   wheel_autonomy::Polygon2d plg;
//   plg.points = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}};

//   bool is_inside = pt.Inside(plg);

//   EXPECT_EQ(true, is_inside);
// }