#pragma once

#include "wheel_autonomy/common/math/line_segment2.h"
#include "wheel_autonomy/common/math/vec2.h"

namespace wheel_autonomy {
namespace common {
namespace math {

/** @brief reference:
https://github.com/opencv/opencv/blob/4.x/modules/core/include/opencv2/core/types.hpp

pt1 = pt2 + pt3;
pt1 = pt2 - pt3;
pt1 = pt2 * a;
pt1 = a * pt2;
pt1 = pt2 / a;
pt1 += pt2;
pt1 -= pt2;
pt1 *= a;
pt1 /= a;
double value = norm(pt); // L2 norm
pt1 == pt2;
pt1 != pt2;

*/

template <typename _Tp>
class Point2 {
 public:
  Point2(_Tp _x, _Tp _y) : x(_x), y(_y) {}

  bool IsLeft(LineSegment2<_Tp> _line_seg) {}

  /**
   * @brief Check whether the point is inside a polygon
   *
   * @param _polygon the input polygon
   * @return true the point is inside specified polygon
   * @return false the point is not inside specified polygon, include on the
   * border of polygon
   */
  bool Inside(Polygon2<_Tp> _polygon);

 public:
  _Tp x;
  _Tp y;
};

using Point2d = Point2<double>;

/////////////////////////////////Implement/////////////////////////////////////

template <typename _Tp>
bool Point2<_Tp>::Inside(Polygon2<_Tp> _polygon) {
  return true;
}

}  // namespace math
}  // namespace common
}  // namespace wheel_autonomy