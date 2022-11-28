#include "wheel_autonomy/common/lookup_table/lut.h"

#include <array>
#include <cmath>

namespace wheel_autonomy {
namespace common {
namespace lut {

namespace {
// Set lookup table sample size. Larger value, more accurate, but more space
// cost. When kLookupTableSampleSize is 20000, error less than 0.0057degree
constexpr int kLookupTableSampleSize = 20000;
static_assert(kLookupTableSampleSize % 2 == 0,
              "kLookupTableSampleSize must be even");
constexpr int kLookupTableSampleSize_2 = kLookupTableSampleSize / 2;

// https://stackoverflow.com/questions/56207065/creating-a-lookup-table-at-compile-time
#if __cplusplus >= 201703L
// calculate lookup table at compile time, works with C++17
constexpr std::array<float, kLookupTableSampleSize + 1>
ConstructAtanLookupTable() {
  std::array<float, kLookupTableSampleSize + 1> lut{0};
  for (int i = 0; i <= kLookupTableSampleSize; ++i) {
    float value = 2.0 / kLookupTableSampleSize * i - 1;
    lut[i]      = std::atan(value);
  }
  return lut;
}

constexpr std::array<float, kLookupTableSampleSize + 1> kAtanLookupTable =
    ConstructAtanLookupTable();
#elif __cplusplus >= 201402L
constexpr float GetAtanValueByLutIndex(std::size_t index) {
  return std::atan(2.0 / kLookupTableSampleSize * index - 1);
}

template <std::size_t... I>
constexpr auto LookupHelper(std::index_sequence<I...>) {
  return std::array<float, sizeof...(I)>({GetAtanValueByLutIndex(I)...});
}

template <std::size_t N>
constexpr auto ConstructLookupTable() {
  return LookupHelper(std::make_index_sequence<N>());
}

// Calculate lookup table at compile time, works with C++14
constexpr std::array<float, kLookupTableSampleSize + 1> kAtanLookupTable =
    ConstructLookupTable<kLookupTableSampleSize + 1>();
#else
static_assert(false, "Not support compile calculate lut before c++14");
#endif

std::size_t GetLutIndex(float x) {
  // use static_cast replace round for performance
  return static_cast<std::size_t>(kLookupTableSampleSize_2 * (x + 1));
}

}  // namespace

float Atan2LookUp(float y, float x) {
  if (x == 0.0f) {
    if (y < 0.0f) {
      return -M_PI_2;
    } else if (y > 0.0f) {
      return M_PI_2;
    } else {
      return 0.0f;
    }
  }
  if (y == 0.0f) {
    if (x < 0.0f) {
      return M_PI;
    } else if (x > 0.0f) {
      return 0.0f;
    }
  }

  float ret;

  if (std::abs(x) < std::abs(y)) {
    ret = kAtanLookupTable[GetLutIndex(x / y)];
    ret = static_cast<float>(x * y > 0 ? M_PI_2 - ret : -M_PI_2 - ret);
  } else {
    ret = kAtanLookupTable[GetLutIndex(y / x)];
  }

  if (x < 0) {
    ret = static_cast<float>(y < 0 ? ret - M_PI : ret + M_PI);
  }

  return ret;
}

}  // namespace lut
}  // namespace common
}  // namespace wheel_autonomy