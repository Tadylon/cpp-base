#include <iostream>
#include <cstring>

void memorycopy() {
    char src[] = "Hello";
    char dest[10];
    memcpy(dest, src, 6);  // 复制 "Hello" + '\0'
    // dest = "Hello"
    std::cout <<  src << std::endl;
    std::cout <<  dest << std::endl;
}

void memorymove() {
    char str[] = "1234567890";
    memmove(str + 3, str, 5);  // 重叠复制
    // str = "1231234590"
    std::cout <<  str << std::endl;
    
    // ❌ memcpy 如果重叠，结果是未定义的
    // memcpy(str + 3, str, 5);  // 危险！
}

void memoryset() {

    char str[10];
    memset(str, 'A', 5);   // 前5个字节设为 'A'
    // str = "AAAAA"
    
    int arr[10];
    memset(arr, 0, sizeof(arr));  // 全部清零
    
    // ⚠️ 注意：只能用于字节填充
    // int arr[10];
    memset(arr, 1, sizeof(arr));  // 每个字节是 1，不是每个 int 是 1！
    // 结果：每个 int = 0x01010101，不是 1
}



// int memcmp(const void* ptr1, const void* ptr2, size_t n);
void memorycmp() {
    char a[] = "ABC";
    char b[] = "ABD";
    int result = memcmp(a, b, 3);
    // result < 0，因为 'C' < 'D'
}


// void* memchr(const void* ptr, int value, size_t n);
void memorychar() {

    char str[] = "Hello World";
    char* found = (char*)memchr(str, 'W', 11);
    if (found) {
        printf("find it : %s\n", found);  // "World"
    }
}


int main()
{

    return 0;
}