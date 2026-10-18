#include <iostream>
#include <string>
#include <utility>

//如果 noexcept 函数内部实际抛出了异常，程序不会去尝试 catch 它，
//而是会直接调用 std::terminate() 终止进程（这是一种“崩溃式”的安全，防止异常逃逸破坏 C++ 的栈展开机制）。

void safe_func() noexcept;          // 承诺绝不抛异常
void risky_func() noexcept(false);  // 可能抛异常（默认就是 false）


template<typename T>
void swap(T& a, T& b) noexcept(noexcept(T(std::move(a)))) {
    // 只有当 T 的移动构造是 noexcept 时，这个 swap 才是 noexcept
}

void f1();               // 类型是 void()
void f2() noexcept;      // 类型是 void() noexcept
//noexcept 是“性能++”的关键，尤其是为了让 vector 扩容时用“搬”而不是“复制”


int main(){
    // 判断 int 加法是否 noexcept（通常是 true）
    auto safe = noexcept(1 + 2); 
    std::cout << "the value of safe : " << safe << std::endl;
    return 0;
}