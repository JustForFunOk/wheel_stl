#pragma once

#include <vector>

#include "wheel_autonomy/common/math/point2.h"

namespace wheel_autonomy {
namespace common {
namespace geometry {

/**
 * @brief last point is same as first point
 *
 */
template <typename _Tp>
class Polygon2 {
 public:
  Polygon2() {}

  std::vector<Point2<_Tp>>& points() const;

  bool IsConvexHull() {}

 protected:
  std::vector<Point2<_Tp>> points;
};

using Polygon2d = Polygon2<double>;

/////////////////////////////////Implement/////////////////////////////////////

}  // namespace geometry
}  // namespace common
}  // namespace wheel_autonomy