#include <iostream>
#include <utility>
#include <string>



// 被调用的函数
void print(std::string& s) {
    std::cout << "左值引用: " << s << std::endl;
}

void print(std::string&& s) {
    std::cout << "右值引用: " << s << std::endl;
}

void print(const std::string& s) {
    std::cout << "const 左值引用: " << s << std::endl;
}

// 完美转发包装器
template<typename T>
void wrapper(T&& arg) {
    // 保持 arg 的原始属性转发
    print(std::forward<T>(arg));
}

int main() {
    std::string str = "Hello";
    const std::string cstr = "World";
    
    wrapper(str);                    // 传递左值 -> 左值引用
    wrapper(cstr);                   // 传递 const 左值 -> const 左值引用
    wrapper(std::string("Temp"));         // 传递右值 -> 右值引用
    wrapper(std::move(str));              // 传递右值 -> 右值引用
    
    return 0;
}