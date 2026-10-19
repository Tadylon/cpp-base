#include <iostream>

// 打印数组的函数
void printArray(int arr[], int size) {
    // 证明它是个指针：sizeof(arr) 在64位系统下是 8 字节，而不是整个数组的大小！
    // std::cout << sizeof(arr) << std::endl; 

    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n' << std::endl;
}

int main() {
    int myArr[] = {1, 2, 3, 4, 5};
    int n = sizeof(myArr) / sizeof(myArr[0]); // 计算数组元素个数：总大小 / 单个元素大小

    // 传参时，直接写数组名即可
    printArray(myArr, n); 
    return 0;
}