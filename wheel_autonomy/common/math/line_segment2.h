#pragma once

#include "wheel_autonomy/common/math/point2.h"
#include "wheel_autonomy/common/math/vec2.h"

namespace wheel_autonomy {
namespace common {
namespace math {

enum class PointToLineSegmentPosition {
  kLeft,   // point is left of the line segment
  kOn,     // point is on the line segment
  kRight,  // point is right of the line segment
};

template <typename _Tp>
class LineSegment2 {
 public:
  LineSegment2(const Point2<_Tp>& _start_pt, const Point2<_Tp>& _end_pt);
  LineSegment2(_Tp _start_pt_x, _Tp _start_pt_y, _Tp _end_pt_x, _Tp _end_pt_y);

  PointToLineSegmentPosition GetPointPosition(const Point2<_Tp>& _point) const;

 protected:
  Point2<_Tp> start_point_;
  Point2<_Tp> end_point_;
};

using LineSegment2d = LineSegment2<double>;

/////////////////////////////////Implement/////////////////////////////////////

template <typename _Tp>
LineSegment2<_Tp>::LineSegment2(const Point2<_Tp>& _start_pt,
                                const Point2<_Tp>& _end_pt)
    : start_point_(_start_pt), end_point_(_end_pt) {}

template <typename _Tp>
LineSegment2<_Tp>::LineSegment2(_Tp _start_pt_x,
                                _Tp _start_pt_y,
                                _Tp _end_pt_x,
                                _Tp _end_pt_y)
    : start_point_(_start_pt_x, _start_pt_y),
      end_point_(_end_pt_x, _end_pt_y) {}

template <typename _Tp>
PointToLineSegmentPosition LineSegment2<_Tp>::GetPointPosition(
    const Point2<_Tp>& _point) const {
  //  point(a)  line_segment(b->c)
  //
  //                 * c(end_point_)
  //   *            /
  //   a(_point)   /
  //              /
  //             * b(start_point_)
  //
  Vec2<_Tp> ba(_point.x - start_point_.x, _point.y - start_point_.y);
  Vec2<_Tp> bc(end_point_.x - start_point_.x, end_point_.y - start_point_.y);
  auto cross_product_result = ba.CrossProduct(bc);

  auto point_position = PointToLineSegmentPosition::kOn;
  if (cross_product_result < 0) {
    point_position = PointToLineSegmentPosition::kLeft;
  } else if (cross_product_result > 0) {
    point_position = PointToLineSegmentPosition::kRight;
  }

  return point_position;
}

}  // namespace math
}  // namespace common
}  // namespace wheel_autonomy