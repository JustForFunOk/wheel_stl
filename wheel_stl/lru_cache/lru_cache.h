#pragma once

#include <cstddef>  // std::size_t
#include <forward_list>
#include <unordered_map>

namespace wheel_stl {

class LRUCache {
 public:
  typedef int key;
  typedef int value;

 public:
  LRUCache(std::size_t _capacity);
  void Put(int _key, int _value);
  int Get(int _key);

 private:
  std::size_t capacity_;  // 储存最大容量

  // 为了实现O(1)调整node顺序 需要使用list
  // 约定：放到list最前面的为最久未使用的
  std::forward_list<int> lru_key_list_;

  // 为了实现O(1)的查询，需要使用unordered_map储存Cache中已有的key_value
  std::unordered_map<key, value> key_value_map_;
};

LRUCache::LRUCache(std::size_t _capacity) : capacity_(_capacity) {}

void LRUCache::Put(int _key, int _value) {}

int LRUCache::Get(int _key) {
  if (key_value_map_.find(_key) != key_value_map_.end()) {
    return key_value_map_[_key];
  }
  return -1;
}

}  // namespace wheel_stl