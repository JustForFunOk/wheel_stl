#pragma once

namespace wheelstl {

template <typename T>
class vector {
 public:
  // empty container constructor
  vector() : data(nullptr), size(0), capability(0) {}

  // fill constructor
  explicit vector(size_t n) {
    data = new T[n];
    size = n;
    capability = n;
  }

  ~vector() {
    if (data) {
      delete[] data;
      size = 0;
      capability = 0;
    }
  }

 private:
  T* data;
  size_t size;
  size_t capability;
};

}  // namespace wheelstl
