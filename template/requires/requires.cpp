#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <cstdint>
#include <cstddef>
#include <type_traits>

template<typename T>
requires std::is_arithmetic_v<T> && (!std::is_same_v<std::remove_cv_t<T>, bool>)
void test(T t)
{
    
}

// 2. 使用 requires 子句
template <typename T>
    requires std::is_copy_constructible_v<T> && (!std::is_pointer_v<T>)
void safe_copy(T a) {
    // ...
}


template<typename T>
requires requires(T x) { std::cout << x; } // 第一个 requires 是子句，第二个是表达式！
void print(T x) {
    std::cout << x << '\n';
}




// 1. 定义概念：要求类型 T 支持流输出操作符
template<typename T>
concept Printable = requires(std::ostream& os, T x) {
    { os << x } -> std::same_as<std::ostream&>; // 既测试了支持 <<，又检查了链式返回类型
};

// 2. 约束函数模板（使用紧凑的 Concept auto 语法）
void print_item(const Printable auto& item) {
    std::cout << "[Printable Item]: " << item << '\n';
}

// 自定义一个满足条件的结构体
struct User {
    std::string name;
    friend std::ostream& operator<<(std::ostream& os, const User& u) {
        return os << "User(" << u.name << ")";
    }
};

// 自定义一个不满足条件的结构体
struct NonPrintableStruct {};

int main() {
    print_item(42);                // 正确：int 原生支持流输出
    print_item("Hello World");     // 正确：const char* 支持流输出
    print_item(User{"Alice"});     // 正确：重载了 operator<<

    NonPrintableStruct obj;
    // print_item(obj); // 编译错误！编译器会明确提示：NonPrintableStruct does not satisfy Printable
}








