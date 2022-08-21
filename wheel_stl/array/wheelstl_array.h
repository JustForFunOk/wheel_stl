#pragma once

/*
why add const?
warning: 'constexpr' non-static member function will not be implicitly 'const' in C++14; add 'const' to avoid a change in behavior [-Wconstexpr-not-const]

noexcept
at()函数由于会检查是否越界，会抛出异常，所以不能用noexcept修饰

constexpr
array size()在编译期间就能计算出来，所以用constexpr修改，减少运行时间

*/

#include <stdexcept>  // std::out_of_range
#include <iterator>   // std::reverse_iterator

namespace wheelstl {

template <typename _Tp, std::size_t _Nm>
class array {
  public:
    // Member types
    typedef _Tp                 value_type;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef value_type*         pointer;
    typedef const value_type*   const_pointer;  // TODO: 为何这里不是_Tp const*或const _Tp const*?
    typedef value_type*         iterator;       // TODO: 这里和pointer有啥区别？
    typedef const value_type*   const_iterator;
    typedef std::reverse_iterator<iterator>  reverse_iterator;
    typedef std::reverse_iterator<const_iterator>  const_reverse_iterator;
    typedef std::size_t         size_type;

    // No explicit Constructor & Destructor

    // Iterators
    iterator begin() noexcept {
        return iterator(data());
    }

    constexpr iterator end() noexcept {
        return iterator(data() + size());
    }

    constexpr const_iterator cbegin() const noexcept {
        return const_iterator(data());
    }

    constexpr const_iterator cend() const noexcept {
        return const_iterator(data() + size());
    }

    constexpr reverse_iterator rbegin() noexcept {  // 注意返回的是reverse_iterator
        // return reverse_iterator(data() + size() - 1);
        return reverse_iterator(end());  // reverse_iterator直接将end()变为rbegin()!!
    }

    constexpr reverse_iterator rend() noexcept {  // 注意返回的是reverse_iterator
        return reverse_iterator(begin());
    }

    constexpr const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(cend());
    }

    constexpr const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(cbegin());
    }

    // Capability
    /**
     * @brief Return the number of elements in the array container.
     * 
     * 在编译期间就能确定，所以用constexpr修饰
     */
    constexpr size_type size() const noexcept {
        return _Nm;
    }

    /**
     * @brief Return the maximum number of elements that the array container can hold.
     * 
     * 完全等同于size(), 只是为了和其他container保持接口一致
     */
    constexpr size_type max_size() const noexcept {
        return _Nm;
    }

    /**
     * @brief Test whether the array is empty
     * 
     * 在编译期间就能确定，所以用constexpr修饰
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
     * @brief Returns a const reference to the element at position n in the array container.
     * If the array object is const-qualified, the function returns a const_reference.
     * 
     * @overload const构成重载，被const修饰的对象会调用const成员函数
     * @param n Position of an element in the array. Start from 0.
     * @return const_reference The element at the specified position in the array.
     */
    const_reference operator[](size_type n) const noexcept {
        return data_[n];
    }

    /**
     * @brief Return a reference to the element at the position n in the array.
     * 
     * Contrast with member operator[], this function checks whether n is within the bounds of valid elements in the container.
     * 
     * 会检查索引所否越界，越界则抛出异常，所以不能加noexcept
     * 
     * @param n Position of an element in the array. Start from 0.
     * @return reference The element at the specified position in the array.
     */
    reference at(size_type n) noexcept {
        return n < _Nm ? data_[n] :
        (std::out_of_range("out of range"), data_[n]);  // 逗号表达式，为了能通过编译，实际永远不会返回data_[n]
    }

    const_reference at(size_type n) const noexcept {
        return n < _Nm ? data_[n] :
        (std::out_of_range("out of range"), data_[n]);  // 逗号表达式，为了能通过编译，实际永远不会返回data_[n]
    }

    constexpr reference front() noexcept {
        return *begin();
    }

    constexpr const_reference front() const noexcept {
        return const_reference(*cbegin());
    }

    constexpr reference back() noexcept {
        return *(end() - 1);
    }

    constexpr const_reference back() const noexcept {
        return const_reference(*(cend() - 1));
    }

    pointer data() noexcept{
        return data_;
    }

    const_pointer data() const noexcept{
        return data_;
    }

    // Modifiers
    void fill(const value_type& val) {
        for (std::size_t i = 0UL; i < _Nm; ++i) {
            data_[i] = val;
        }
    }

    void swap(array& x) {
        array& tmp = x;
        x = *this;
        *this = tmp;
    }

  public:
    // 为了使用列表初始化方法 array<int, 2> arr{1,2}; 需要将成员变量定义为public
    // 参考： https://en.cppreference.com/w/cpp/language/aggregate_initialization
    _Tp data_[_Nm];
};

// 针对size为0的array，使用模版偏特化来实现


}  // end of namespace wheelstl