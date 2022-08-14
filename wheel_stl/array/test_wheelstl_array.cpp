
#include <gtest/gtest.h>
#include <iostream>
#include <array>

#include "wheel_stl/array/wheelstl_array.h"

TEST(WheelStlArray, sizeof) {
  std::array<int, 10> arr;
  EXPECT_EQ(40, sizeof(arr));

  wheelstl::array<int, 10> wheel_arr;
  EXPECT_EQ(sizeof(arr), sizeof(wheel_arr));

  // corner case: empty array
  wheelstl::array<int, 0> empty_arr;
  EXPECT_EQ(0, sizeof(empty_arr));
}

TEST(WheelStlArray, capability) {
  wheelstl::array<int, 10> wheel_arr;

  // size
  EXPECT_EQ(10, wheel_arr.size());

  // max_size
  EXPECT_EQ(10, wheel_arr.max_size());

  // empty
  EXPECT_EQ(false, wheel_arr.empty());

  wheelstl::array<int, 0> empty_arr;
  EXPECT_EQ(true, empty_arr.empty());
}

TEST(WheelStlArray, element_access) {
  wheelstl::array<int, 10> wheel_arr;

  EXPECT_EQ(0, wheel_arr[0]);
}