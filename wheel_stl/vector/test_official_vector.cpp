// https://www.cplusplus.com/reference/vector/vector/

#include <gtest/gtest.h>
#include <vector>

TEST(Vector, sizeof) {
  std::vector<int> vec;
  EXPECT_EQ(24, sizeof(vec));
}

TEST(Vector, constructor) {
  // empty container constructor
  {
    std::vector<int> vec;
    EXPECT_EQ(0, vec.size());
  }

  // fill constructor 1
  {
    const int kElementNum = 5;  // 5 elements
    std::vector<int> vec(kElementNum);
    EXPECT_EQ(kElementNum, vec.size());
  }

  {
    // fill constructor 2
    const int kElementNum = 3;    // 3 elements
    const int kValue      = 100;  // with value 100

    std::vector<int> fill_vec(kElementNum, kValue);

    EXPECT_EQ(kElementNum, fill_vec.size());
    for (size_t i = 0; i < fill_vec.size(); ++i) {
      EXPECT_EQ(kValue, fill_vec[i]);
    }

    // range constructor
    std::vector<int> range_vec(fill_vec.begin(), fill_vec.end());

    EXPECT_EQ(kElementNum, range_vec.size());
    for (size_t i = 0; i < range_vec.size(); ++i) {
      EXPECT_EQ(kValue, range_vec[i]);
    }

    // copy constructor
    std::vector<int> copy_vec(range_vec);
    EXPECT_EQ(kElementNum, copy_vec.size());
    for (size_t i = 0; i < copy_vec.size(); ++i) {
      EXPECT_EQ(kValue, copy_vec[i]);
    }

    // move constructor (C++11)
    std::vector<int> move_rec(std::move(copy_vec));
    EXPECT_EQ(kElementNum, move_rec.size());
    for (size_t i = 0; i < move_rec.size(); ++i) {
      EXPECT_EQ(kValue, move_rec[i]);
    }
    // after move, copy_vec is in an unspecified but valid state.
    // https://godbolt.org/z/GMMM7Pfhf
    EXPECT_EQ(0, copy_vec.size());
    EXPECT_EQ(true, copy_vec.empty());
  }

  {
    // initializer list (C++11)
    std::vector<int> list_vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(10, list_vec.size());
    for (size_t i = 0; i < list_vec.size(); ++i) {
      EXPECT_EQ(i, list_vec[i]);
    }
  }
}

TEST(Vector, destructor) {
  // how test destructor?
}
