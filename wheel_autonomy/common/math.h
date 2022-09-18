// dot product
// cross product
// vec

#pragma once

namespace wheelautonomy {

template <typename _Tp>
class Vec2 {
 public:
  Vec2() {}
  Vec2(_Tp _x, _Tp _y) : x(_x), y(_y) {}

  /**
   * @brief https://en.wikipedia.org/wiki/Dot_product
   *
   * @param _another another vector
   * @return _Tp the result of dot product
   */
  _Tp DotProduct(const Vec2<_Tp>& _another) const {
    return this->x * _another.x + this->y * _another.y;
  }

  /**
   * @brief https://en.wikipedia.org/wiki/Cross_product
   *
   * @param _aonther another vector
   * @return _Tp the result of cross product
   */
  _Tp CrossProduct(const Vec2<_Tp>& _another) const {
    return this->x * _another.y - this->y * _another.x;
  }

 public:
  _Tp x;
  _Tp y;
};

using Vec2d = Vec2<double>;

}  // namespace wheelautonomy