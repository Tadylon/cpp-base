#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <type_traits>


#ifdef BASE

// 原始函数：接受一个字符串，显示其值
void process(std::string& s) {
    std::cout << "左值引用: " << s << std::endl;
}

void process(std::string&& s) {
    std::cout << "右值引用: " << s << std::endl;
}

// ❌ 问题：我们希望写一个包装函数，将参数原封不动地传给 process()
// 尝试1：传值 - 会导致额外拷贝
void wrapper_1(std::string s) {
    process(s);  // 永远传递左值，无法调用右值版本
}

// 尝试2：使用 const 引用 - 只能传递 const，无法修改
// void wrapper_2(const std::string& s) {
//     process(s);  // 编译错误：无法将 const 转换为非 const
// }

// 尝试3：为左值和右值分别写重载 - 代码爆炸
void wrapper_3(std::string& s) { process(s); }
void wrapper_3(std::string&& s) { process(std::move(s)); }  // 需要区分 N 种情况
#else

// 不是所有 && 都是右值引用！
template<typename T>
void foo(T&& arg) {  // 这是万能引用（Universal Reference）
    // arg 的类型取决于传入的参数：
    // - 传入左值 -> T 是 左值引用，arg 是 左值引用
    // - 传入右值 -> T 是 非引用，arg 是 右值引用
}


// ✅ 万能引用
template<typename T>
void func1(T&& arg);

template<typename T>
void func2(typename std::remove_reference<T>::type&& arg);  // 不是万能引用（没有类型推导）

// ❌ 不是万能引用（固定类型）
void func3(std::string&& arg);  // 右值引用

// ❌ 不是万能引用（vector 的 &&）
template<typename T>
void func4(std::vector<T>&& arg);  // 右值引用

// ❌ 不是万能引用（const 修饰）
template<typename T>
void func5(const T&& arg);  // 右值引用



// std::forward 的简化实现（C++11 版本）
template<typename T>
T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
    return static_cast<T&&>(arg);
}

template<typename T>
T&& forward(typename std::remove_reference<T>::type&& arg) noexcept {
    static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
    return static_cast<T&&>(arg);
}







#endif
