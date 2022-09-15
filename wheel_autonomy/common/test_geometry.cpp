#include <gtest/gtest.h>
#include "wheel_autonomy/common/geometry.h"

TEST(Point, Point2d) {
  wheelautonomy::Point2d pt(1.0, 1.0);

  EXPECT_DOUBLE_EQ(1.0, pt.x);
  EXPECT_DOUBLE_EQ(1.0, pt.y);
}

TEST(Polygon, Polygon2d) {
  wheelautonomy::Polygon2d plg;
  plg.points = {{0,0}, {2,0}, {2,2}, {0,2}, {0,0}};

  EXPECT_EQ(5, plg.points.size());

}

TEST(Point, Inside) {
  wheelautonomy::Point2d pt(1.0, 1.0);

  wheelautonomy::Polygon2d plg;
  plg.points = {{0,0}, {2,0}, {2,2}, {0,2}, {0,0}};

  bool is_inside = pt.Inside(plg);

  EXPECT_EQ(true, is_inside);
}