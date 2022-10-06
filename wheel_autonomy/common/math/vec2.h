#pragma once

#include "wheel_autonomy/common/math/point2.h"

namespace wheel_autonomy {
namespace common {
namespace math {

template <typename _Tp>
class Vec2 {
 public:
  Vec2() {}
  Vec2(_Tp _x, _Tp _y) : x(_x), y(_y) {}
  Vec2(const Point2<_Tp>& _start_pt, const Point2<_Tp>& _end_pt);

  /**
   * @brief https://en.wikipedia.org/wiki/Dot_product
   *
   * @param _another Another vector
   * @return _Tp The value of dot product
   */
  _Tp DotProduct(const Vec2<_Tp>& _another) const;

  /**
   * @brief https://en.wikipedia.org/wiki/Cross_product
   * Not return a vector, just get the cross product value on z-axis direction.
   * @param _another Another vector
   * @return _Tp The value of cross product on z-axis direction
   */
  _Tp CrossProduct(const Vec2<_Tp>& _another) const;

 public:
  _Tp x;
  _Tp y;
};

using Vec2d = Vec2<double>;

/////////////////////////////////Implement/////////////////////////////////////

template <typename _Tp>
Vec2<_Tp>::Vec2(const Point2<_Tp>& _start_pt, const Point2<_Tp>& _end_pt) {
  this->x = _end_pt.x - _start_pt.x;
  this->y = _end_pt.y - _start_pt.y;
}

template <typename _Tp>
_Tp Vec2<_Tp>::DotProduct(const Vec2<_Tp>& _another) const {
  // a * b = a_x * b_x + a_y * b_y
  return this->x * _another.x + this->y * _another.y;
}

template <typename _Tp>
_Tp Vec2<_Tp>::CrossProduct(const Vec2<_Tp>& _another) const {
  // a x b = a_x * b_y - a_y * b_x
  return this->x * _another.y - this->y * _another.x;
}

}  // namespace math
}  // namespace common
}  // namespace wheel_autonomy