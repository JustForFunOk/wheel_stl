#pragma once

#include <exception>  // runtime_error
#include <string>     // to_string
#include <vector>     // vector

#include "wheel_autonomy/common/math/line_segment2.h"
#include "wheel_autonomy/common/math/point2.h"

namespace wheel_autonomy {
namespace common {
namespace math {

/**
 * @brief Point in polygon algorithm, different algorithm suit for different
 * polygon https://en.wikipedia.org/wiki/Point_in_polygon
 */
enum class PointInPolygonMethod {
  kCrossProduct,   // only works with convex polygons (仅适用于凸多边形)
  kRayCasting,     // default, works with convex and concave polygons
                   // （凸多边形和凹多边形均适用）
  kWindingNumber,  // even works with self intersections polygons
                   // (最通用，甚至可以处理自相交的多边形，但自动驾驶场景中很少有这种情况)
};

/**
 * @brief last point is same as first point, clockwise or counterclockwise
 *
 */
template <typename _Tp>
class Polygon2 {
 public:
  Polygon2() {}

  std::vector<Point2<_Tp>>& Points();

  const std::vector<Point2<_Tp>>& Points() const;

  bool IsConvexHull() {}

  /**
   * @brief Check whether a point is inside the polygon
   *
   * @param _point The input point
   * @param _method See PointInPolygonMethod for details
   *
   * @return true The point is inside specified polygon
   * @return false The point is not inside specified polygon, include on the
   * border of polygon
   */
  template <typename Method>  // C++17
  bool IsPointInside(const Point2<_Tp>& _point) const;

 private:
  bool IsPointInsideUsingCrossProduct(const Point2<_Tp>& _point) const;

 protected:
  std::vector<Point2<_Tp>> points_;
};

using Polygon2d = Polygon2<double>;

/////////////////////////////////Implement/////////////////////////////////////
template <typename _Tp>
std::vector<Point2<_Tp>>& Polygon2<_Tp>::Points() {
  return this->points_;
}

template <typename _Tp>
const std::vector<Point2<_Tp>>& Polygon2<_Tp>::Points() const {
  return this->points_;
}

template <typename _Tp>
template <typename Method>  // 注意写法，template function in template class
bool Polygon2<_Tp>::IsPointInside(const Point2<_Tp>& _point) const {
  if constexpr (std::is_same_v<Method, PointInPolygonMethod::kCrossProduct>) {
    return IsPointInsideUsingCrossProduct(_point);
  }
}

/// 实现原理：
/// 点在凸多边形每一条边的左边或每一条边的右边，则说明该点在该凸多边形内
template <typename _Tp>
bool Polygon2<_Tp>::IsPointInsideUsingCrossProduct(
    const Point2<_Tp>& _point) const {
  auto polygon_points_size = this->Points().size();

  if (polygon_points_size < 4) {
    throw std::runtime_error(
        "polygon points size is less than 4, current size is " +
        std::to_string(polygon_points_size));
  }

  LineSegment2d line_seg(points_[0], points_[1]);
  // get point position relative to first line segment
  auto point_position = line_seg.GetPointPosition(_point);
  if (PointToLineSegmentPosition::kOn == point_position) {
    return false;
  }

  // start from the second line segment
  for (std::size_t i = 2; i < polygon_points_size; ++i) {
    LineSegment2d line_seg(points_[i - 1], points_[i]);
    // once the point is found in the other side of line segment, the point is
    // outside of polygon
    if (point_position != line_seg.GetPointPosition(_point)) {
      return false;
    }
  }

  return true;
}

}  // namespace math
}  // namespace common
}  // namespace wheel_autonomy