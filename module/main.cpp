// main.cpp - Client Code
import math; // 导入 math 模块，无需 #include
#include <iostream> // 标准库头文件仍可照常使用

int main() {
    std::cout << add(3, 4) << '\n'; // 输出: 7
    // multiply(3, 4); // 错误：multiply 未被导出，此调用无法编译
    return 0;
}