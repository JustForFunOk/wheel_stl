#pragma once

#include <vector>

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
  CrossProduct,   // only works with convex polygons (仅适用于凸多边形)
  RayCasting,     // works with convex and concave polygons
                  // （凸多边形和凹多边形均适用）
  WindingNumber,  // even works with self intersections polygons
                  // (自相交的多边形)
};

/**
 * @brief last point is same as first point, clockwise or counterclockwise
 *
 */
template <typename _Tp>
class Polygon2 {
 public:
  Polygon2() {}

  std::vector<Point2<_Tp>>& Points() const;

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
  bool IsPointInside(
      const Point2<_Tp>& _point,
      PointInPolygonMethod _method = PointInPolygonMethod::RayCasting) const;

 private:
  bool IsPointInsideUsingCrossProduct(const Point2<_Tp>& _point) const;

 protected:
  std::vector<Point2<_Tp>> points;
};

using Polygon2d = Polygon2<double>;

/////////////////////////////////Implement/////////////////////////////////////
template <typename _Tp>
bool Polygon2<_Tp>::IsPointInside(const Point2<_Tp>& _point,
                                  PointInPolygonMethod _method) const {
  bool is_point_inside = false;
  switch (_method) {
    case PointInPolygonMethod::CrossProduct:
      is_point_inside = IsPointInsideUsingCrossProduct(_point);
      break;
    case PointInPolygonMethod::RayCasting:
      // TODO
      break;
    case PointInPolygonMethod::WindingNumber:
      // TODO
      break;
  }
  return is_point_inside;
}

template <typename _Tp>
bool Polygon2<_Tp>::IsPointInsideUsingCrossProduct(
    const Point2<_Tp>& _point) const {
  return true;
}

}  // namespace math
}  // namespace common
}  // namespace wheel_autonomy