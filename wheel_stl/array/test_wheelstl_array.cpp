
#include <gtest/gtest.h>
#include <iostream>
#include <array>

#include "wheel_stl/array/wheelstl_array.h"

TEST(WheelStlArray, sizeof) {
  wheelstl::array<int, 10> wheel_int_arr;
  EXPECT_EQ(40, sizeof(wheel_int_arr));

  wheelstl::array<char, 10> wheel_char_arr;
  EXPECT_EQ(10, sizeof(wheel_char_arr));
}

TEST(WheelStlArray, constructor) {
  // default constructor
  wheelstl::array<int, 5> arr;

  // initialize list
  wheelstl::array<int, 5> arr2{0,1,2,3,4};
  wheelstl::array<int, 5> arr3 = {0,1,2,3,4};

  // copy constructor
  wheelstl::array<int, 5> arr4(arr2);
  wheelstl::array<int, 5> arr5 = arr4;

  // assign operator =
  arr = arr5;

  for(size_t i = 0UL; i < arr.size(); i++) {
    EXPECT_EQ(i, arr[i]);
    EXPECT_EQ(i, arr2[i]);
    EXPECT_EQ(i, arr3[i]);
    EXPECT_EQ(i, arr4[i]);
    EXPECT_EQ(i, arr5[i]);
  }

  // move constructor
  wheelstl::array<int, 5> arr6(std::move(arr5));

  // move operator =
  arr = std::move(arr4);

  for(size_t i = 0UL; i < arr.size(); i++) {
    EXPECT_EQ(i, arr[i]);
    EXPECT_EQ(i, arr6[i]);

    // array is still valid after move
    EXPECT_EQ(i, arr5[i]);
    EXPECT_EQ(i, arr4[i]);
  }

}

TEST(WheelStlArray, capability) {
  wheelstl::array<int*, 5> wheel_arr;
  const wheelstl::array<char, 5> const_wheel_arr{'h','e','l','l','o'};

  // size
  EXPECT_EQ(5, wheel_arr.size());
  EXPECT_EQ(5, const_wheel_arr.size());

  // max_size
  EXPECT_EQ(5, wheel_arr.max_size());
  EXPECT_EQ(5, const_wheel_arr.max_size());

  // empty
  EXPECT_EQ(false, wheel_arr.empty());
  EXPECT_EQ(false, const_wheel_arr.empty());
}

TEST(WheelStlArray, element_access) {
  {
  wheelstl::array<int, 5> wheel_arr{1,2,3,4,5};

  // operator[]
  wheel_arr[1] = 22;            // lvalue
  EXPECT_EQ(22, wheel_arr[1]);  // rvalue

  // at()
  wheel_arr[2] = 33;               // lvalue
  EXPECT_EQ(33, wheel_arr.at(2));  // rvalue
  EXPECT_ANY_THROW(wheel_arr.at(5));  // out of range

  // front()
  wheel_arr.front() = 11;            // lvalue
  EXPECT_EQ(11, wheel_arr.front());  // rvalue

  // end()
  wheel_arr.back() = 55;             // lvalue
  EXPECT_EQ(55, wheel_arr.back());   // rvalue

  // data()
  *(wheel_arr.data()+3) = 44;            // lvalue
  EXPECT_EQ(44, *(wheel_arr.data()+3));  // rvalue
  }

  // const-qualified
  {
  const wheelstl::array<int, 5> wheel_arr{11,22,33,44,55};

  // operator[]
  EXPECT_EQ(22, wheel_arr[1]);  // rvalue

  // at()
  EXPECT_EQ(33, wheel_arr.at(2));  // rvalue
  EXPECT_ANY_THROW(wheel_arr.at(5));  // out of range

  // front()
  EXPECT_EQ(11, wheel_arr.front());  // rvalue

  // end()
  EXPECT_EQ(55, wheel_arr.back());   // rvalue

  // data()
  EXPECT_EQ(44, *(wheel_arr.data()+3));  // rvalue
  }
}

TEST(WheelStlArray, iterators) {
  {
  wheelstl::array<int, 3> wheel_arr = {1,2,3};

  // begin()  end()
  std::for_each(wheel_arr.begin(), wheel_arr.end(), [](int& ele){ele--;});  // wheel_arr = {0,1,2};

  // cbegin()  cend()
  for (auto it = wheel_arr.cbegin(); it != wheel_arr.cend(); it++)
  {
    auto distance = std::distance(wheel_arr.cbegin(), it);
    EXPECT_EQ(distance, *it);
  }
  }

  {
  wheelstl::array<int, 3> wheel_arr = {3,2,1};

  // rbegin() rend()
  std::for_each(wheel_arr.rbegin(), wheel_arr.rend(), [](int& ele){ele--;});  // wheel_arr = {2,1,0};

  // crbegin()  cend()
  for (auto it = wheel_arr.crbegin(); it != wheel_arr.crend(); it++)
  {
    auto distance = std::distance(wheel_arr.crbegin(), it);
    EXPECT_EQ(distance, *it);
  }
  }
}

TEST(WheelStlArray, Modifiers) {
  wheelstl::array<int, 6> arr;

  // fill
  arr.fill(5);
  for(const auto ele : arr) {
    EXPECT_EQ(5, ele);
  }

  wheelstl::array<int,5> first = {10, 20, 30, 40, 50};
  wheelstl::array<int,5> second = {11, 22, 33, 44, 55};

  wheelstl::array<int, 5> first_backup(first);
  wheelstl::array<int, 5> second_backup(second);

  // swap
  first.swap(second);

  for(std::size_t i = 0UL; i < first.size(); ++i) {
    EXPECT_EQ(first[i], second_backup[i]);
    EXPECT_EQ(second[i], first_backup[i]);
  }

}

// corner case: empty array

TEST(WheelStlArray, empty_array) {
  wheelstl::array<int, 0> empty_arr;

  // sizeof
  // 对于empty-array，不同版本各有自己的实现（linux版本sizeof为1，macos版本sizeof为4），sizeof无法保证。
  // EXPECT_EQ(1, sizeof(empty_arr));

  // iterators
  EXPECT_EQ(nullptr, empty_arr.begin());
  EXPECT_EQ(nullptr, empty_arr.end());

  EXPECT_EQ(empty_arr.rend(), empty_arr.rbegin());

  EXPECT_EQ(nullptr, empty_arr.cbegin());
  EXPECT_EQ(nullptr, empty_arr.cend());

  EXPECT_EQ(empty_arr.crend(), empty_arr.crbegin());

  // capability
  EXPECT_EQ(0, empty_arr.size());
  EXPECT_EQ(0, empty_arr.max_size());
  EXPECT_EQ(true, empty_arr.empty());

  // element access

  // modifier
}

