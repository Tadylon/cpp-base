#include <iostream>
#include <string>
#include <cstring>


// char* strcpy(char* dest, const char* src);
void stringcopy() {

    char dest[10];
    strcpy(dest, "Hello");     // 安全：5个字符
    strcpy(dest, "Hello World"); // ❌ 溢出！dest 只有10字节
}

