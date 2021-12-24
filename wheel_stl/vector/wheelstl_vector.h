#pragma once

namespace wheelstl {

template <typename T>
class vector {
 public:
  // empty container constructor
  vector() : start_(nullptr), end_(nullptr), end_of_capability_(nullptr) {}

  // fill constructor 1
  explicit vector(size_t n) {
    start_ = new T[n];
    end_ = start_ + n;
    end_of_capability_ = end_;
  }

  /**
   * @brief fill constructor
   * @param n the number of element
   * @param val init val of element
   */
  vector(size_t n, const T& val) {
    start_ = new T[n];
    end_ = start_ + n;
    end_of_capability_ = end_;
    for (auto i = start_; i != end_; ++i) {
      *i = val;
    }
  }

  ~vector() {
    if (start_) {
      delete[] start_;
      start_ = nullptr;
      end_ = nullptr;
      end_of_capability_ = nullptr;
    }
  }

  // size()
  size_t size() { return end_ - start_; }

  /**
   * @brief operator []
   * @param n the n-th element of vector
   */
  T& operator[](size_t n) { return *(start_ + n); }

  /**
   * @brief get the first iterator of vector
   */
  T* begin() { return start_; }

 private:
  T* start_;
  T* end_;
  T* end_of_capability_;
};

}  // namespace wheelstl
