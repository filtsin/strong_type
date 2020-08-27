# Strong type

Strong type for named parameters without implicit conversion

For example,

```c++
void foo(int width, int height) {
    . . .
}
. . .
int width = 4;
int height = 5;
foo(height, width); // wrong order => Compiles
```

# Usage 

```c++
#include <strong_type/strong_type.hpp>

using width_t = strong_type<int>;
using height_t = strong_type<int>;

void foo(width_t width, height_t height) {
    . . .
}
. . .
auto width = width_t { 4 };
auto height = height_t { 5 };
foo(height, width); // wrong order => Fail compile
```

`strong_type` is fully transparent for operators. For example if we have `strong_type<T>` and 
T implements operator+ then `strong_type<T>` implements it too. (Now `operator++` and `operator--` (post and pre) are not supported)

You can overload some operators. For example if I want multiplication to return a different type:

```c++
struct Foo { int v; };

using int_t = strong_type<int>;
using foo_t = strong_type<Foo>;

// std::is_same<decltype(int_t{ 1 } * int{ 2 }), int_t>::value

foo_t operator*(const int_t &lhs, const int_t &rhs) {
    return foo_t { Foo { lhs.underlying() * rhs.underlying() * 2 } };
}

// Now std::is_same<decltype(int_t{ 1 } * int{ 2 }), foo_t>::value
```

`strong_type` has special case for support input and output operators.