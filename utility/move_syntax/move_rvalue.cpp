#include <iostream>
#include <vector>
#include <utility>

#include "standard_time.h"
#include "print_obj.h"

class MyString {
    char* data;
public:
    // 移动构造函数
    MyString(MyString&& other) noexcept 
        : data(other.data) {         // 1. 窃取指针
        other.data = nullptr;        // 2. 将源对象置为“空壳”状态
    }

    // 移动赋值运算符
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data;           // 1. 释放当前资源
            data = other.data;       // 2. 窃取指针
            other.data = nullptr;    // 3. 源对象置空
        }
        return *this;
    }

    ~MyString() {
        cout__("Destructor ! ");
        delete[] data; 
    }
};

std::vector<int> createBigVector() {
    std::vector<int> v(1000000, 42);
    return v;  // 返回时，按旧标准会拷贝整个容器（1百万个整数）
}



int main() {
    int x = 10;
    int& lref = x;        // 正确：左值引用绑定左值
    int&& rref = 20;      // 正确：右值引用绑定临时值（字面量）
    // int&& rref2 = x;      // 错误！右值引用不能绑定左值
    {
        Timer timer("copy");
        std::vector<int> big = createBigVector(); 
        // 这里发生了两次拷贝（虽然编译器做了优化，但逻辑上仍存在风险）
    }
    std::vector<int> a = {2,54,23};
    std::cout << "the value of vectora is : ";
    PrintContainer(a);
    {
        Timer timer("move");
        std::vector<int> b = std::move(a);
        PrintContainer(b);
    }
    PrintContainer(a);

    //push_back + move_syntax
    std::vector<std::string> vec;
    std::string s = "very long string...";
    vec.push_back(std::move(s));  // O(1) 移动，而非 O(n) 拷贝
    // 此时 s 为空，资源已转移
    PrintContainer(vec);
    std::cin.get();
    return 0;
}







