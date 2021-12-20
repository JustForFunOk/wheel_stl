#pragma once

namespace wheelstl {

template <typename T>
class vector {
 public:
  // empty container constructor
  vector() : data_(nullptr), size_(0), capability_(0) {}

  // fill constructor 1
  explicit vector(size_t n) {
    data_ = new T[n];
    size_ = n;
    capability_ = n;
  }

  /**
   * @brief fill constructor
   * @param n the number of element
   * @param val init val of element
   */
  vector(size_t n, const T& val) {
    data_ = new T[n];
    size_ = n;
    capability_ = n;
    for (size_t i = 0; i < n; ++i) {
      *(data_ + i) = val;
    }
  }

  ~vector() {
    if (data_) {
      delete[] data_;
      size_ = 0;
      capability_ = 0;
    }
  }

  // size()
  size_t size() { return size_; }

  /**
   * @brief get the first iterator of vector
   */
  T* begin() { return data_; }

 private:
  T* data_;
  size_t size_;
  size_t capability_;
};

}  // namespace wheelstl
