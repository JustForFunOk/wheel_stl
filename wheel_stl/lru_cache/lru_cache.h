#pragma once

#include <algorithm>      // std::for_each
#include <cstddef>        // std::size_t
#include <iostream>       // std::cout std::endl
#include <list>           // std::list
#include <unordered_map>  // std::unordered_map
#include <utility>        // std::pair std::make_pair

namespace wheel_stl {

class LRUCache {
 public:
  typedef int lru_key;
  typedef int lru_value;

 public:
  LRUCache(std::size_t _capacity);
  void Put(const int& _lru_key, const int& _lru_value);
  int Get(int _lru_key);

 private:
  bool IsCacheFull() const { return lru_key_value_list_.size() >= capacity_; }

  void UpdateElementToLatestUsed(const int& _lru_key);

  void PrintListForDebug() const {
    std::cout << "PrintListForDebug start" << std::endl;
    std::for_each(
        lru_key_value_list_.begin(), lru_key_value_list_.end(), [&](auto ele) {
          std::cout << ele.first << ", " << ele.second << std::endl;
        });
    std::cout << "PrintListForDebug end" << std::endl;
  }
  void PrintMapForDebug() const {
    std::cout << "PrintMapForDebug start" << std::endl;
    std::for_each(lru_key_list_node_map_.begin(),
                  lru_key_list_node_map_.end(),
                  [&](auto ele) { std::cout << ele.first << std::endl; });
    std::cout << "PrintMapForDebug end" << std::endl;
  }

 private:
  std::size_t capacity_;  // 储存最大容量

  // 需要使用链表:
  // 为了实现O(1)调整元素顺序(把最近刚使用的调整到最前面)

  // 需要使用双向链表:
  // 需要在front()插入新元素,在back()删除元素
  // forward_list只有front(),list有front()和back()

  // 链表中需要同时储存key和value:
  // 删除list中back()元素时,需要知道back()元素的key,用来O(1)同步去unordered_map中删除该元素

  // 约定：从list的front()插入元素,从back()删除元素，故back()为最久未使用的元素
  std::list<std::pair<lru_key, lru_value>> lru_key_value_list_;

  // 需要同时使用unordered_map:
  // 为了实现O(1)的查询
  // key即为lru_key,和list同步插入和删除
  // value为指向的list node的指针
  std::unordered_map<lru_key,
                     std::list<std::pair<lru_key, lru_value>>::iterator>
      lru_key_list_node_map_;
};

LRUCache::LRUCache(std::size_t _capacity) : capacity_(_capacity) {}

void LRUCache::Put(const int& _lru_key, const int& _lru_value) {
  // check lru_key is exist in unordered_map or not
  if (lru_key_list_node_map_.find(_lru_key) == lru_key_list_node_map_.end()) {
    // if not exist, check cache is full or not
    if (IsCacheFull()) {
      // if full, delete first, pop_back from list, delete from unordered_map
      const auto list_back_lru_key = lru_key_value_list_.back().first;
      lru_key_value_list_.pop_back();
      lru_key_list_node_map_.erase(list_back_lru_key);
    }

    // push_front lru_value to list, insert to unordered_map
    lru_key_value_list_.emplace_front(_lru_key, _lru_value);
    lru_key_list_node_map_[_lru_key] = lru_key_value_list_.begin();

  } else {
    // 1. move element to list front, update element position in unordered_map
    UpdateElementToLatestUsed(_lru_key);

    // 2. change value
    lru_key_value_list_.front().second = _lru_value;
  }
}

int LRUCache::Get(int _lru_key) {
  if (lru_key_list_node_map_.find(_lru_key) != lru_key_list_node_map_.end()) {
    // 1. move element to list front, update element position in unordered_map
    UpdateElementToLatestUsed(_lru_key);

    // 2. return value
    return lru_key_list_node_map_[_lru_key]->second;
  }
  return -1;
}

void LRUCache::UpdateElementToLatestUsed(const int& _lru_key) {
  lru_key_value_list_.emplace_front(*lru_key_list_node_map_[_lru_key]);
  lru_key_value_list_.erase(lru_key_list_node_map_[_lru_key]);

  lru_key_list_node_map_[_lru_key] = lru_key_value_list_.begin();
}

}  // namespace wheel_stl