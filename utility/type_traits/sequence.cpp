// #pragma once
#include <iostream>
#include <type_traits>
#include <cstring>
#include <cstdint>
#include <sstream>


// 为了演示递归指针，定义一个简单的类
struct MyData {
    double value;
    int64_t id;
    // 注：为了支持递归，需要提供 tie 或者直接特化 serialize，
    // 但此处因为类分支未实现，我们先跳过，只用基础类型演示
};

// 前置声明（用于递归）
template<typename T>
void serialize(const T& obj, std::ostream& os);

// 主调度函数：利用 if constexpr（C++17）在编译期消灭分支
template<typename T>
void serialize(const T& obj, std::ostream& os) {
    if constexpr (std::is_arithmetic_v<T>) {
        // 1. 如果是整数/浮点，直接按字节写入（零开销）
        os.write(reinterpret_cast<const char*>(&obj), sizeof(T));
    } 
    else if constexpr (std::is_pointer_v<T>) {
        // 2. 如果是指针：先存地址（用于调试），再解引用序列化内容
        os << "Ptr Address: " << (void*)obj << " -> ";
        if constexpr (std::is_arithmetic_v<std::remove_pointer_t<T>>) {
            // 指向算术类型的指针，直接写值
            os << *obj;
        } else {
            // 指向对象的指针，递归调用
            serialize(*obj, os);
        }
    } 
    else if constexpr (std::is_class_v<T>) {
        // 3. 如果是类（假设有 tie 方法，结合你之前的提问），递归遍历成员
        // obj.tie() 返回 tuple，逐字段递归调用 serialize
        // ... 此处省略展开逻辑
        os << "Class Object";
    }
}

// 标准库在 C++20 中定义的内置 Concept：
template<typename T>
concept Integral = std::is_integral_v<T>; // 本质上还是调用了 Type Traits

// 编译期判断类型是否可拷贝的 Concept：
template<typename T>
concept Copyable = std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>;

template<Integral T>
void print(T x) { 
    std::cout << x; 
}  // 只接受整数

// void print(Copyable<> auto x) ; // 如果定义了该函数

int main()
{
    std::stringstream ss;  // 用字符串流捕获输出，方便查看

    // 1. 测试算术类型
    int a = 42;
    serialize(a, ss);
    std::cout << "Arithmetic: " << ss.str() << std::endl; 
    // 输出乱码（二进制），因为 os.write 直接写内存，人类不可读

    // 2. 测试指针（指向算术类型）
    ss.str("");  // 清空流
    int num = 100;
    int* p = &num;
    serialize(p, ss);
    std::cout << "Pointer to int: " << ss.str() << std::endl;
    // 输出类似：Ptr Address: 0x7ffc... -> 100

    // 3. 测试指针（指向类对象）
    ss.str("");
    MyData data{3.14, 10};
    MyData* pData = &data;
    serialize(pData, ss);
    std::cout << "Pointer to class: " << ss.str() << std::endl;
    // 输出：Ptr Address: 0x... -> MyData{id=10, value=3.14}

    // 4. 测试 Concepts 用法（单独演示）

    print(5);   // OK
    // print(5.0); // 编译错误
    std::cout << "Demo finished." << std::endl;


    return 0;
}