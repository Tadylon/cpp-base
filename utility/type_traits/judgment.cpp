#include <iostream>
#include <concepts>
#include <type_traits>

//简要写一下std::integral
template <typename T>
concept Integral = std::is_integral_v<T>;

// 编译期判断类型是否可拷贝的 Concept：
template<typename T>
concept Copyable = std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>;

template <typename T>
void print_type_info() {
    if constexpr (std::is_integral_v<T>) { // C++17 的 _v 后缀，直接获取编译期值
        std::cout << "this is a int type \n";
    } else if constexpr (std::is_pointer_v<T>) {
        std::cout << "this is a pointer type \n";
    } else {
        std::cout << "other types \n";
    }
}


// 直接在参数里限制
void integral_function(std::integral auto x) {
    std::cout << "the value of x is : " << x << "\n";
}

template <std::integral T>
void integral_only_tem(T x) {  
    std::cout << "the value of x is : " << x << "\n";
};

// 或者
template <typename T>
void integral_only_(T x) requires std::is_integral_v<T> {
    std::cout << "the value of x is : " << x << "\n";
};


int main()
{
    integral_function(39);
    integral_only_tem(432);
    integral_only_(32);

    return 0;
}