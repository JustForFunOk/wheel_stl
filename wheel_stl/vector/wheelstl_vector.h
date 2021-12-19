#pragma once

namespace wheelstl {

template <typename T>
class vector {
 public:
  // empty container constructor
  vector() : data_(nullptr), size_(0), capability_(0) {}

  // fill constructor
  explicit vector(size_t n) {
    data_ = new T[n];
    size_ = n;
    capability_ = n;
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

 private:
  T* data_;
  size_t size_;
  size_t capability_;
};

}  // namespace wheelstl
