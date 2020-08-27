#ifndef IMPL_TRAITS_INCLUDE
#define IMPL_TRAITS_INCLUDE
#pragma once

#include <type_traits>
#include <utility>

namespace strong_t {

struct no {};

#define IMPL_OPERATOR_TRAIT(name, op) \
template <typename T, typename U> \
no operator op(T &lhs, const U &rhs); \
template <typename Lhs, typename Rhs = Lhs> \
struct name { \
    static constexpr bool value = !std::is_same<decltype(std::declval<Lhs&>() op std::declval<Rhs>()), no>::value; \
}


// Compare
IMPL_OPERATOR_TRAIT(has_eq, ==);
IMPL_OPERATOR_TRAIT(has_greater, >);
IMPL_OPERATOR_TRAIT(has_less, <);
IMPL_OPERATOR_TRAIT(has_less_eq, <=);
IMPL_OPERATOR_TRAIT(has_greater_eq, >=);

// Arithmetic
IMPL_OPERATOR_TRAIT(has_plus, +);
IMPL_OPERATOR_TRAIT(has_plus_eq, +=);
IMPL_OPERATOR_TRAIT(has_minus, -);
IMPL_OPERATOR_TRAIT(has_minus_eq, -=);
IMPL_OPERATOR_TRAIT(has_div, /);
IMPL_OPERATOR_TRAIT(has_div_eq, /=);
IMPL_OPERATOR_TRAIT(has_mul, *);
IMPL_OPERATOR_TRAIT(has_mul_eq, *=);

// Binary
IMPL_OPERATOR_TRAIT(has_bit_or, |);
IMPL_OPERATOR_TRAIT(has_bit_or_eq, |=);
IMPL_OPERATOR_TRAIT(has_bit_and, &);
IMPL_OPERATOR_TRAIT(has_bit_and_eq, &=);
IMPL_OPERATOR_TRAIT(has_bit_xor, ^);
IMPL_OPERATOR_TRAIT(has_bit_xor_eq, ^=);
IMPL_OPERATOR_TRAIT(has_bit_shift_right, >>);
IMPL_OPERATOR_TRAIT(has_bit_shift_right_eq, >>=);
IMPL_OPERATOR_TRAIT(has_bit_shift_left, <<);
IMPL_OPERATOR_TRAIT(has_bit_shift_left_eq, <<=);

#undef IMPL_OPERATOR_TRAIT

}

#endif
