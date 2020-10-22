#ifndef IMPL_STRONG_TYPE_INCLUDE
#define IMPL_STRONG_TYPE_INCLUDE
#pragma once

#include <strong_type/impl/traits.hpp>
#include <type_traits>
#include <utility>
#include <iosfwd>

template <typename T, typename UniqueTag>
class strong_type {
public:
    using underlying_t = typename std::remove_reference<T>::type;

    explicit strong_type(T val) : value(std::move(val)) { }

    underlying_t& underlying() { return value; }
    const underlying_t& underlying() const { return value; }


#define IMPL_OPERATOR_BOOL(trait, op) \
template <typename U = underlying_t, typename = typename std::enable_if<strong_t:: trait<const U&>::value>::type> \
friend bool operator op(const strong_type &lhs, const strong_type &rhs) { return lhs.value op rhs.value; }

    IMPL_OPERATOR_BOOL(has_eq, ==)
    IMPL_OPERATOR_BOOL(has_less, <)
    IMPL_OPERATOR_BOOL(has_less_eq, <=)
    IMPL_OPERATOR_BOOL(has_greater, >)
    IMPL_OPERATOR_BOOL(has_greater_eq, >=)

#undef IMPL_OPERATOR_BOOL

#define IMPL_OPERATOR_ARITHMETIC(trait, op) \
template <typename U = underlying_t, typename = typename std::enable_if<strong_t:: trait<U>::value>::type> \
friend strong_type operator op(strong_type lhs, const strong_type &rhs) { lhs.value = lhs.value op rhs.value; return lhs; }

#define IMPL_SELF_OPERATOR_ARITHMETIC(trait, op) \
template <typename U = underlying_t, typename = typename std::enable_if<strong_t:: trait<U>::value>::type> \
strong_type& operator op(const strong_type &rhs) { value op rhs.value; return *this; }

    // Arithmetic

    IMPL_OPERATOR_ARITHMETIC(has_plus, +)
    IMPL_SELF_OPERATOR_ARITHMETIC(has_plus_eq, +=)
    IMPL_OPERATOR_ARITHMETIC(has_minus, -)
    IMPL_SELF_OPERATOR_ARITHMETIC(has_minus_eq, -=)
    IMPL_OPERATOR_ARITHMETIC(has_div, /)
    IMPL_SELF_OPERATOR_ARITHMETIC(has_div_eq, /=)
    IMPL_OPERATOR_ARITHMETIC(has_mul, *)
    IMPL_SELF_OPERATOR_ARITHMETIC(has_mul_eq, *=)

    // Binary

    IMPL_OPERATOR_ARITHMETIC(has_bit_or, |)
    IMPL_SELF_OPERATOR_ARITHMETIC(has_bit_or_eq, |=)
    IMPL_OPERATOR_ARITHMETIC(has_bit_and, &)
    IMPL_SELF_OPERATOR_ARITHMETIC(has_bit_and_eq, &=)
    IMPL_OPERATOR_ARITHMETIC(has_bit_xor, ^)
    IMPL_SELF_OPERATOR_ARITHMETIC(has_bit_xor_eq, ^=)
    IMPL_OPERATOR_ARITHMETIC(has_bit_shift_left, >>)
    IMPL_SELF_OPERATOR_ARITHMETIC(has_bit_shift_right_eq, >>=)
    IMPL_OPERATOR_ARITHMETIC(has_bit_shift_left, <<)
    IMPL_SELF_OPERATOR_ARITHMETIC(has_bit_shift_left_eq, <<=)

    // Output overload

    template <typename U = underlying_t, typename = typename std::enable_if<strong_t::has_bit_shift_left<std::ostream&, U>::value>::type>
    friend std::ostream& operator<<(std::ostream &os, const strong_type &rhs) {
        os << rhs.value;
        return os;
    }

    // Input overload

    template <typename U = underlying_t, typename = typename std::enable_if<strong_t::has_bit_shift_right<std::istream&, U&>::value>::type>
    friend std::istream& operator>>(std::istream &is, strong_type &rhs) {
        is >> rhs.value;
        return is;
    }

#undef IMPL_OPERATOR_ARITHMETIC
#undef IMPL_SELF_OPERATOR_ARITHMETIC

private:
    T value;
};

#endif
