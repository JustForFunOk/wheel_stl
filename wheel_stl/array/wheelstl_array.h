#pragma once

/*
why add const?
warning: 'constexpr' non-static member function will not be implicitly 'const' in C++14; add 'const' to avoid a change in behavior [-Wconstexpr-not-const]
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

    tyoedef std::size_t           size_type;


    // Iterators


    // Capability
    /**
     * @brief Return the number of elements in the array container.
     */
    constexpr std::size_t size() const noexcept {
        return _Nm;
    }

    /**
     * @brief Return the maximum number of elements that the array container can hold.
     */
    constexpr std::size_t max_size() const noexcept {
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
     * @brief 
     * 
     */
    _Tp& operator[](std::size_t n) {
        return data[n];
    }

    // Modifiers

  private:
    _Tp data[_Nm];
};

}  // end of namespace wheelstl