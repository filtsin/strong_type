#include <gtest/gtest.h>
#include <strong_type/strong_type.hpp>
#include <utility>


TEST(underly_type, underlying_t) {
    using foo_t = strong_type<int>;
    ASSERT_TRUE((std::is_same<decltype(std::declval<foo_t>().underlying()), int&>::value));
    using bar_t = strong_type<int&>;
    ASSERT_TRUE((std::is_same<decltype(std::declval<bar_t>().underlying()), int&>::value));
    using baz_t = strong_type<int&&>;
    ASSERT_TRUE((std::is_same<decltype(std::declval<baz_t>().underlying()), int&>::value));
}

using int_t = strong_type<int>;
struct Foo {};
using foo_t = strong_type<Foo>;

TEST(operators, compare_op) {
    bool v = strong_t::has_eq<const int_t&>::value;
    ASSERT_TRUE(v);
    ASSERT_FALSE(strong_t::has_eq<const foo_t&>::value);
}

TEST(operators, arithmetic_op) {
    bool v = strong_t::has_plus<int_t>::value;
    ASSERT_TRUE(v);
    ASSERT_FALSE(strong_t::has_plus<foo_t>::value);

    v = strong_t::has_plus_eq<int_t>::value;
    ASSERT_TRUE(v);
    ASSERT_FALSE(strong_t::has_plus_eq<foo_t>::value);
}


TEST(operators, binary_op) {
    bool v = strong_t::has_bit_or<int_t>::value;
    ASSERT_TRUE(v);
    ASSERT_FALSE(strong_t::has_bit_or<foo_t>::value);
}

TEST(operators, output_op) {
    bool v = strong_t::has_bit_shift_left<std::ostream&, int_t>::value;
    ASSERT_TRUE(v);
    ASSERT_FALSE((strong_t::has_bit_shift_left<std::ostream&, foo_t>::value));
}

TEST(operators, input_op) {
    bool v = strong_t::has_bit_shift_right<std::istream&, int_t&>::value;
    ASSERT_TRUE(v);
    ASSERT_FALSE((strong_t::has_bit_shift_right<std::istream&, foo_t&>::value));
}
