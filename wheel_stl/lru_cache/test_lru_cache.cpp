#include <gtest/gtest.h>

#include "wheel_stl/lru_cache/lru_cache.h"

TEST(LRUCache, usage) {
  wheel_stl::LRUCache lru_cache(2);

  lru_cache.Put(1, 1);              // 1
  lru_cache.Put(2, 2);              // 2 1
  EXPECT_EQ(1, lru_cache.Get(1));   // 1 2
  lru_cache.Put(3, 3);              // 3 1
  EXPECT_EQ(-1, lru_cache.Get(2));  // not found
}