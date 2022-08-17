#pragma once

/*
why add const?
warning: 'constexpr' non-static member function will not be implicitly 'const' in C++14; add 'const' to avoid a change in behavior [-Wconstexpr-not-const]

noexcept
at()函数由于会检查是否越界，会抛出异常，所以不能用noexcept修饰

constexpr
array size()在编译期间就能计算出来，所以用constexpr修改，减少运行时间

*/


namespace wheelstl {

template <typename _Tp, std::size_t _Nm>
class array {
  public:
    // Member types
    typedef _Tp                 value_type;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef _Tp*                pointer;
    typedef const _Tp*          const_pointer;
    typedef _Tp*                iterator;
    typedef const _Tp*          const_iterator;

    typedef std::size_t         size_type;


    // Iterators


    // Capability
    /**
     * @brief Return the number of elements in the array container.
     */
    constexpr size_type size() const noexcept {
        return _Nm;
    }

    /**
     * @brief Return the maximum number of elements that the array container can hold.
     */
    constexpr size_type max_size() const noexcept {
        return _Nm;
    }

    /**
     * @brief Test whether the array is empty
     */
    constexpr bool empty() const noexcept {
        return size() == 0;
    }

    //Element access
    /**
     * @brief Returns a reference to the element at position n in the array container.
     * 
     * @param n Position of an element in the array. Start from 0.
     * @return reference The element at the specified position in the array.
     */
    reference operator[](size_type n) noexcept {
        return data_[n];
    }

    /**
     * @brief If the array object is const-qualified, the function returns a const_reference.
     * 如何调用到这个函数？
     * 
     * @overload const 构成重载？
     * @param n 
     * @return const_reference 
     */
    const_reference operator[](size_type n) const noexcept {
        return data_[n];
    }

    /**
     * @brief Return a reference to the element at the position n in the array.
     * 
     * Contrast with member operator[], this function checks whether n is within the bounds of valid elements in the container.
     * 
     * @param n Position of an element in the array. Start from 0.
     * @return reference The element at the specified position in the array.
     */
    reference at(size_type n) noexcept {
        return data_[n];
    }

    const_reference at(size_type n) const noexcept {
        return data_[n];
    }

    // Modifiers

  private:
    _Tp data_[_Nm];
};

}  // end of namespace wheelstl