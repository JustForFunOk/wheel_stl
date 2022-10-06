#pragma once

#include "wheel_autonomy/common/math/point2.h"

namespace wheel_autonomy {
namespace common {
namespace math {

template <typename _Tp>
class LineSegment2 {
 public:
  LineSegment2(const Point2<_Tp>& _start_pt, const Point2<_Tp>& _end_pt);
  LineSegment2(_Tp _start_pt_x, _Tp _start_pt_y, _Tp _end_pt_x, _Tp _end_pt_y);

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

}  // namespace math
}  // namespace common
}  // namespace wheel_autonomy