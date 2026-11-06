
# Concepts



在 C++20 中，Concepts 语言级特性对 Type Traits 进行了封装和语法简化，使约束更具可读性：

```cpp
#include <type_traits>
#include <concepts>

// 定义一个 Concept，底层依然基于 type trait
template <typename T>
concept Number = std::is_arithmetic_v<T>;

// 1. 直接约束函数参数
void process(Number auto x) {
    // ...
}

// 2. 使用 requires 子句
template <typename T>
requires std::is_copy_constructible_v<T> && (!std::is_pointer_v<T>)
void safe_copy(T a) {
    // ...
}
```

C++20 及以后： 接口约束首选 concepts 与 requires。


