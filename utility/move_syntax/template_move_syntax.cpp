#include <iostream>
#include <string>



template<typename T>
void wrapper(T&& arg) { // 传入左值时 T 是 int&，传入右值时 T 是 int
    // 完美转发给实际函数
    // actualFunc(std::forward<T>(arg)); 
}

int mian()
{

    int x = 10;
    wrapper(x);  // 转发左值
    wrapper(20); // 转发右值（移动语义）
    return  0;
}


