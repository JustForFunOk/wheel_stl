#include <gtest/gtest.h>
#include <vector>

TEST(Vector, Constructor) {
  std::vector<int> vec;
  EXPECT_EQ(0, vec.size());
}
