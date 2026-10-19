#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>

#include "print_obj.h"

int main() {
    // 基本声明：键是 string，值是 int
    std::map<std::string, int> ages;
    
    // 初始化方式1：直接赋值
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 22;
    
    // 初始化方式2：使用初始化列表（C++11）
    std::map<std::string, int> scores = {
        {"Math", 95},
        {"English", 88},
        {"Science", 92}
    };
    
    // 初始化方式3：使用 pair
    std::map<int, std::string> students = {
        std::make_pair(1, "Alice"),
        std::make_pair(2, "Bob"),
        {3, "Charlie"}  // C++11 简化语法
    };
    
    ages["John"] = 23;
    // cout__(ages);
    for (const auto& i : ages) {
        std::cout << i.first << ": " << i.second << std::endl;
    }

    std::cout << "\nthe second ways to print :\n";
    for (const auto& [name, age]  : ages) {
        std::cout << name << ": " << age << std::endl;
    }
    // ages.insert({"Charly",25});
    ages.insert({"Charly",25});
    std::cout << "\ninsert again :\n";
    for (const auto& [name, age]  : ages) {
        std::cout << name << ": " << age << std::endl;
    }
    
    ages.insert({"Eve",43});
    std::cout << "\ninsert again :\n";
    for (const auto& [name, age]  : ages) {
        std::cout << name << ": " << age << std::endl;
    }
    auto result = ages.insert({"Charlie",22});
    if (!result.second) {
        std::cout << "insert fail ! " << std::endl;
    }
    else {
        std::cout << "insert successfully ! " << std::endl;
    }
    return 0;
}














