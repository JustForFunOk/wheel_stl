#include "wheel_autonomy/common/math/polygon2.h"

#include <gtest/gtest.h>

using namespace wheel_autonomy::common::math;

TEST(Polygon2, Constructor) {
  Polygon2d plg;
  plg.Points() = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}};

  EXPECT_EQ(5, plg.Points().size());
}

TEST(Point2, InsideCrossProductMethod) {
  Polygon2d plg;
  plg.Points() = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}};

  {  // Inside
    Point2d pt(1.0, 1.0);
    bool is_inside =
        plg.template IsPointInside<PointInPolygonMethod::kCrossProduct>(pt);
    EXPECT_EQ(true, is_inside);
  }

  {  // On
    Point2d pt(2, 1);
    bool is_inside = plg.IsPointInside<PointInPolygonMethod::kCrossProduct>(pt);
    EXPECT_EQ(false, is_inside);
  }

  {  // Outside
    Point2d pt(2.1, 1);
    bool is_inside = plg.IsPointInside<PointInPolygonMethod::kCrossProduct>(pt);
    EXPECT_EQ(false, is_inside);
  }
}