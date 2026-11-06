#include <concepts>
#include <type_traits>

template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};



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