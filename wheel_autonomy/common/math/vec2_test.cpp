#include "wheel_autonomy/common/math/vec2.h"

#include <gtest/gtest.h>
#include <Eigen/Dense>  // use eigen as ground truth

using namespace wheel_autonomy::common::math;

TEST(Vec2d, Constructor) {
  Vec2d a;

  Vec2d b(1.0, 1.0);
  EXPECT_DOUBLE_EQ(1.0, b.x);
  EXPECT_DOUBLE_EQ(1.0, b.y);

  // Point2d start_pt(1.0, 1.0);
  // Point2d end_pt(2.0, 2.0);
  // Vec2d c(start_pt, end_pt);
  // EXPECT_DOUBLE_EQ(1.0, c.x);
  // EXPECT_DOUBLE_EQ(1.0, c.y);
}

TEST(Vec2d, DotProduct) {
  Vec2d a(1.0, 1.0);
  Vec2d b(1.0, 0);

  Eigen::Vector2d c(1.0, 1.0);
  Eigen::Vector2d d(1.0, 0);

  EXPECT_DOUBLE_EQ(a.DotProduct(b), c.dot(d));
  EXPECT_DOUBLE_EQ(a.DotProduct(b), 1.0);

  EXPECT_DOUBLE_EQ(a.DotProduct(b), b.DotProduct(a));
}

TEST(Vec2d, CrossProduct) {
  Vec2d a(1.0, 1.0);
  Vec2d b(1.0, 0);

  // cross product is only for vectors of size 3 in eigen.
  Eigen::Vector3d c(1.0, 1.0, 0);
  Eigen::Vector3d d(1.0, 0, 0);

  double ab = a.CrossProduct(b);
  double cd = c.cross(d)[2];  // the value on z-axis

  EXPECT_DOUBLE_EQ(ab, cd);
  EXPECT_DOUBLE_EQ(ab, -1.0);

  double ba = b.CrossProduct(a);
  double dc = d.cross(c)[2];  // the value on z-axis

  EXPECT_DOUBLE_EQ(ba, dc);
  EXPECT_DOUBLE_EQ(ba, 1.0);
}
