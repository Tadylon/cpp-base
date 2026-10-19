#include <iostream>

// 注意语法：(&arr) 括号不能少，[5] 明确限制了只能传大小为 5 的 int 数组
void processRefArray(int (&arr)[5]) {
    // 此时 sizeof(arr) 就是 5 * 4 = 20 字节！它没有退化！
    for (int i = 0; i < 5; i++) {
        arr[i] += 10;
    }
}

int main() {
    int a[5] = {1, 2, 3, 4, 5};
    int b[3] = {1, 2, 3};

    processRefArray(a); // 正确
    // processRefArray(b); // 错误！编译直接报错，类型不匹配（需要5个，提供了3个）

    return 0;
}