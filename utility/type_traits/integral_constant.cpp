#include <type_traits>
#include <iostream>
#include <functional>
#include <vector>

#include "print_obj.h"
#include "standard_time.h"

// 标准库的内部实现简化
template<typename T, T v>
struct integral_constant_imtate {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant_imtate<T, v>;
    constexpr operator value_type() const noexcept { return value; }
};

// ----- 辅助函数：测试泛型存储 -----
// 这个模板接受任意可调用对象，利用 decay 提取其“可存储类型”
template <typename Callable>
void store_and_call(Callable&& cb) {
    // 核心用法：将传入的可调用对象退化，得到标准的函数指针或可拷贝类型
    using CleanType = std::decay_t<Callable>;
    
    // 静态断言：如果是函数指针或可拷贝对象，才能放入容器
    static_assert(std::is_pointer_v<CleanType> || std::is_copy_constructible_v<CleanType>,
                  "Type must be copyable to store in vector");
    
    // 场景1：将退化后的类型存入 vector（函数类型无法存入，指针可以）
    std::vector<CleanType> vec;
    vec.push_back(cb);  // 如果 cb 是函数，decay 后变指针，可以拷贝
    
    // 场景2：用退化后的类型声明一个变量并调用
    CleanType stored_cb = cb;
    int temp[1] = {99};
    stored_cb(temp, 888);
}

// 函数声明
void func(int a[], int b) {
    std::cout << "func called, b = " << b;
    if (a) {
        std::cout << ", a[0] = " << a[0];
    }
    std::cout << std::endl;
}


int main()
{
    // 两个最常用的别名：
    using true_type = integral_constant_imtate<bool, true>;
    using false_type = integral_constant_imtate<bool, false>;
    
    // 你今后会高频使用的快捷方式（C++17）：
    // 等价于 std::is_integral<int>::value
    auto result_value = std::is_integral_v<int>;   
    cout__(result_value);

    cout__("----------------------------------/n");
    
    auto result_value_ = std::is_integral<int>::value;
    cout__(result_value_);

    auto result_value_type = std::is_integral<int>::value_type();
    cout__(result_value_type);
    
    cout__("----------------------------------/n");
    //这个是什么不知道
    using FuncPointerType = std::decay_t<decltype(func)>; 
    // 结果类型为 void (*)(int*, int)  (函数退化为函数指针)


        // 验证类型是否正确（编译期检查）
    static_assert(std::is_same_v<FuncPointerType, void(*)(int*, int)>, 
                  "Type deduction failed!");
    std::cout << "Type deduction success: void(*)(int*, int)" << std::endl;

    
    // ----- 用法1：直接声明函数指针变量并调用 -----
    FuncPointerType ptr1 = func;   // 等价于 void(*ptr1)(int*,int) = func;
    int arr1[2] = {10, 20};
    ptr1(arr1, 100);  // 输出：func called, b = 100, a[0] = 10



    // ----- 用法2：包装进 std::function（底层需要函数指针类型） -----
    std::function<decltype(func)> wrapper = func;
    int arr2[2] = {30, 40};
    wrapper(arr2, 200); // 输出：func called, b = 200, a[0] = 30

    // ----- 用法3：在泛型模板中存储（传入函数和 lambda 对比） -----
    std::cout << "\n--- Testing generic store ---" << std::endl;
    store_and_call(func);  // 传入函数，内部 decay 为指针
    
    // 传入 Lambda（注意：Lambda 不是函数指针，decay 后会保留其独特的闭包类型，但可拷贝）
    auto lambda = [](int a[], int b) {
        std::cout << "Lambda called, b = " << b << std::endl;
    };
    store_and_call(lambda); // 内部 CleanType 是 lambda 类，可拷贝存储

    // ----- 额外：为什么不使用 decay 会出错？ -----
    // 假设想声明一个 vector 存储 func：
    // std::vector<decltype(func)> vec_error;  // 编译错误！函数类型不能作为 vector 的元素
    std::vector<FuncPointerType> vec_ok;      // 正确，函数指针可以存储
    vec_ok.push_back(func);
    
    std::cout << "\nAll demos completed successfully!" << std::endl;
    return 0;
}