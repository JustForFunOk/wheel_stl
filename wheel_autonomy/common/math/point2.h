#pragma once

#include "wheel_autonomy/common/math/vec2.h"

namespace wheel_autonomy {
namespace common {
namespace math {

template <typename _Tp>
using Point2 = Vec2<_Tp>;

using Point2d = Point2<double>;

}  // namespace math
}  // namespace common
}  // namespace wheel_autonomy