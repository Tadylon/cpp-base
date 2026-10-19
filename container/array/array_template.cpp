#include <iostream>

// T 代表数据类型，N 代表数组大小
template <typename T, unsigned int N>
void printArrayWithTemplate(T (&arr)[N]) {
    std::cout << "当前数组的大小自动推导为: " << N << std::endl;
    for (unsigned int i = 0; i < N; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr1[3] = {1, 2, 3};
    double arr2[5] = {1.1, 2.2, 3.3, 4.4, 5.5};

    printArrayWithTemplate(arr1); // 自动识别为 int 数组，大小 3
    printArrayWithTemplate(arr2); // 自动识别为 double 数组，大小 5

    return 0;
}