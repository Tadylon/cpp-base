#pragma once
#include <iostream>
#include <tuple>
#include <type_traits>

template<typename T>
void PrintIterator(T begin , T end) {
    std::cout << "the value of this iterator is : ";
    for (auto it = begin; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename Container>
void PrintContainer(const Container& container) {
    std::cout << "the elements of this container is : ";
    for (const auto& el : container) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}


// 万能打印器：递归打印 tuple
template<typename Tuple, size_t... Is>
void print_tuple_impl(const Tuple& t, std::index_sequence<Is...>) {
    ((std::cout << std::get<Is>(t) << " "), ...);
}


template<typename... Args>
void print_tuple(const std::tuple<Args...>& t) {
    print_tuple_impl(t, std::index_sequence_for<Args...>{});
}

// -------- 模板打印函数 --------
template<typename T>
void print_all(const T& obj) {
    print_tuple(obj.tie());
}

//判断数据类型，然后决定print出 : none or info
template<typename T>
void cout__(const T& info) {
    //这一行代码没有太大作用，没办法输出名字，只能怪输出一个info
    // std::cout << "info" << " :  ";
    
    // 1. 如果是数组（这里可以区分 char 数组和其他普通数组）
    if constexpr (std::is_array_v<std::remove_reference_t<T>>) {
        using ElementType = std::remove_extent_t<std::remove_reference_t<T>>;
        
        // 如果是字符数组 (char 数组)
        if constexpr (std::is_same_v<ElementType, char> || std::is_same_v<ElementType, const char>) {
            if (info[0] == '\0') {
                std::cout << "none" << std::endl;
            } else {
                std::cout << info << std::endl; // 打印字符串
            }
        } 
        // 如果是普通数组 (如 int 数组)，打印其内容而不是地址
        else {
            std::cout << "[ ";
            for (const auto& item : info) {
                std::cout << item << " ";
            }
            std::cout << "]" << std::endl;
        }
    }
    // 2. 如果是指针类型
    else if constexpr (std::is_pointer_v<T>) {
        if (info == nullptr) {
            std::cout << "none" << std::endl;
        } else if constexpr (std::is_same_v<T, const char*> || std::is_same_v<T, char*>) {
            if (info[0] == '\0') {
                std::cout << "none" << std::endl;
            } else {
                std::cout << info << std::endl;
            }
        } else {
            std::cout << "Pointer(" << info << ")" << std::endl; // 打印其他类型指针地址
        }
    }
    // 3. 如果是 std::string
    else if constexpr (std::is_same_v<T, std::string>) {
        if (info.empty()) {
            std::cout << "none" << std::endl;
        } else {
            std::cout << info << std::endl;
        }
    }
    // 4. 其他基础数据类型 (int, double 等)
    else {
        std::cout << info << std::endl;
    }
}

template<typename T>
void cline__(const T& info) {
    std::cout << info << "\n"; 
}