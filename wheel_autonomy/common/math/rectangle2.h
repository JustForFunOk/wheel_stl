#pragma once

#include "wheel_autonomy/common/math/point2.h"

#include <algorithm>  // std::min std::max
#include <exception>  // std::runtime_error

namespace wheel_autonomy {
namespace common {
namespace math {

/***
 * @brief Rectangle2: Axis-aligned rectangle in 2D plane
 */
template <typename _Tp>
class Rectangle2 {
 public:
  Rectangle2(const Point2<_Tp>& _left_bottom, const Point2<_Tp>& _right_top);

  /***
   * @brief Area: Calculate the rectangle area. Refer to:
   * https://en.wikipedia.org/wiki/Area
   * @return rectangle area.
   */
  _Tp Area() const;

  /***
   * @brief Iou: Calculate the IoU(Intersection over Union) with another
   * rectangle. Refer to: https://en.wikipedia.org/wiki/Jaccard_index
   * @param _another another rectangle
   * @return the value of Iou
   */
  double Iou(const Rectangle2<_Tp>& _another) const;

 public:
  Point2<_Tp> left_bottom;  // left bottom vertex
  Point2<_Tp> right_top;    // right top vertex
};

using Rectangle2d = Rectangle2<double>;

/////////////////////////////////Implement/////////////////////////////////////

template <typename _Tp>
Rectangle2<_Tp>::Rectangle2(const Point2<_Tp>& _left_bottom,
                            const Point2<_Tp>& _right_top)
    : left_bottom(_left_bottom), right_top(_right_top) {}

template <typename _Tp>
_Tp Rectangle2<_Tp>::Area() const {
  _Tp area = (right_top.x - left_bottom.x) * (right_top.y - left_bottom.y);
  if (area <= 0) {
    throw std::runtime_error(
        "rectangle area <= 0, please check input rectangle vertices");
  }
  return area;
}

template <typename _Tp>
double Rectangle2<_Tp>::Iou(const Rectangle2<_Tp>& _another) const {
  // 假设两个矩形相交，计算相交的小矩形的四条边界坐标
  const auto x_left   = std::max(left_bottom.x, _another.left_bottom.x);
  const auto x_right  = std::min(right_top.x, _another.right_top.x);
  const auto y_top    = std::min(right_top.y, _another.right_top.y);
  const auto y_bottom = std::max(left_bottom.y, _another.left_bottom.y);

  // 若左边界比右边界还要靠右，或下边界比上边界还要靠上，则说明两个矩形不相交
  if (x_left >= x_right || y_bottom >= y_top) {
    return 0.0;
  }

  // 计算相交的小矩形的面积
  Rectangle2<_Tp> intersect_rect({x_left, y_bottom}, {x_right, y_top});
  const auto intersection_area = intersect_rect.Area();

  // union部分面积为 两个矩形面积之和减去相交小矩形的面积
  const auto union_area = Area() + _another.Area() - intersection_area;

  const double iou = static_cast<double>(intersection_area) / union_area;

  return iou;
}

}  // namespace math
}  // namespace common
}  // namespace wheel_autonomy
