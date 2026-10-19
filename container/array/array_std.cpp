#include <array>
#include <iostream>

// 传参时直接传引用，非常自然，且带有大小信息
void printModernArray(const std::array<int, 5>& arr) {
    for (int val : arr) {
        std::cout << val << " ";
    }
}

int main() {
    std::array<int, 5> myArr = {1, 2, 3, 4, 5};
    printModernArray(myArr);
    return 0;
}