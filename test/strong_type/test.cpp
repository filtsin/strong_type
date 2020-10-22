#include <gtest/gtest.h>
#include <strong_type/strong_type.hpp>

using meter_t = strong_type<int, struct meter_tag>;

using width_t = strong_type<meter_t, struct width_tag>;
using height_t = strong_type<meter_t, struct height_tag>;

struct rectangle {
public:
    rectangle(width_t width, height_t height) : w(width), h(height) {}

    meter_t get_w() const { return w.underlying(); }
    meter_t get_h() const { return h.underlying(); }


private:
    width_t w;
    height_t h;
};

TEST(basic, usage) {
    const auto rect = rectangle { width_t { meter_t { 3 } }, height_t { meter_t { 4 } } };
    ASSERT_EQ(rect.get_w(), meter_t { 3 });
    ASSERT_EQ(rect.get_h(), meter_t { 4 });
}

TEST(basic, arithmetic) {
    auto v1 = meter_t { 4 };
    auto v2 = meter_t  { 5 };
    auto result = v1 * v2;

    ASSERT_EQ(result, meter_t { 20 });
}

TEST(basic, arithmetic_transparent) {
    using int_t = strong_type<int, struct int_tag>;
    using in_t = strong_type<int_t, struct in_tag>;

    auto var1 = int_t { 4 };
    auto var2 = in_t { var1 };

    var2 += in_t { int_t { 5 }};
    ASSERT_EQ(var2, in_t { int_t { 9 } });
}

