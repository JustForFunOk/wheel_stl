#pragma once

/*
目前先使用STL内置的allocator

*/

#include <iterator>  // std::reverse_iterator
#include <memory>  // std::allocator

namespace wheelstl {

template <typename _Tp, typename Alloc = std::allocator<_Tp>>
class vector {
 public:
  // Member types
  typedef _Tp                value_type;
  typedef Alloc              allocator_type;
  typedef value_type&        reference;
  typedef const value_type&  const_reference;
  typedef value_type*        pointer;
  typedef const value_type*  const_pointer;
  typedef value_type*        iterator;
  typedef const value_type*  const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::size_t        size_type;

  // Constructor
  // empty container constructor
  vector() : start_(nullptr), end_(nullptr), end_of_capability_(nullptr) {}

  // fill constructor 1
  explicit vector(size_type _n) {
    start_             = vec_allocate(_n);
    end_               = start_ + _n;
    end_of_capability_ = end_;
  }

  /**
   * @brief fill constructor
   * @param n the number of element
   * @param val init val of element
   */
  vector(size_type n, const value_type& val) {
    start_             = vec_allocate(_n);
    end_               = start_ + _n;
    end_of_capability_ = end_;
    for (auto i = start_; i != end_; ++i) {
      *i = val;
    }
  }

  ~vector() {
    if (start_) {
      delete[] start_;
      start_             = nullptr;
      end_               = nullptr;
      end_of_capability_ = nullptr;
    }
  }

  // Iterators
  iterator begin() noexcept {
    return iterator(start_);
  }

  iterator end() noexcept {
    return iterator(end_);
  }

  reverse_iterator rbegin() noexcept {
    return reverse_iterator(end());
  }

  reverse_iterator rend() noexcept {
    return reverse_iterator(begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(start_);
  }

  const_iterator cend() const noexcept {
    return const_iterator(end_)
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(cend());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(cbegin());
  }

  // Capability
  size_type size() const{
    return cend() - cbegin();
  }

  // Element access
  /**
   * @brief operator []
   * @param n the n-th element of vector
   */
  T& operator[](size_t n) { return *(start_ + n); }

  /**
   * @brief get the first iterator of vector
   */
  T* begin() { return start_; }

  // Modifiers


 private:
  /**
   * @brief 申请 n*sizeof(T) bytes的内存空间
   * https://en.cppreference.com/w/cpp/memory/allocator/allocate
   *
   * @param n element的数量
   * @return pointer
   */
  pointer vec_allocate(size_type n) {
    // 调用指定的allocator
    return n != 0 ? allocator_type::allocate(n) : nullptr;
  }

 private:
  pointer start_;
  pointer end_;
  pointer end_of_capability_;
};

}  // namespace wheelstl
