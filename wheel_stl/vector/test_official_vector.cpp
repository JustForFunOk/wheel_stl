#include <gtest/gtest.h>
#include <vector>

TEST(Vector, empty_container_constructor) {
  std::vector<int> vec;
  EXPECT_EQ(0, vec.size());
}

TEST(Vector, fill_constructor) {
  {
    std::vector<int> vec(5);  // 5 elements
    EXPECT_EQ(5, vec.size());
  }

  {
    std::vector<int> vec(3, 100);  // 3 ints with value 100
    EXPECT_EQ(3, vec.size());

    for (int i = 0; i < vec.size(); ++i) {
      EXPECT_EQ(100, vec[i]);
    }
  }
}
