#include <iostream>
#include <string>


// void SetValue(const int& value) {
//     std::cout << "the value has set ! " << std::endl;
// }

void SetValue(int&& value) {
    std::cout << "the value has set ! " << std::endl;
}

//lvalue
void PringName(const std::string& name)
{
    std::cout << "lvalue : ";
    std::cout << name << std::endl;
}

//rvalue
void PringName(std::string&& name)
{
    std::cout << "rvalue : ";
    std::cout << name << std::endl;
}

int main()
{
    int a = 10;      // 'a' 是一个左值，它在内存中有确定的位置
    int* p = &a;     // 合法：可以对左值 'a' 取地址
    a = 20;          // 合法：左值可以放在等号左侧
    SetValue(20);
    SetValue(std::move(3234));

    const int b = 5; // 'b' 是一个常量左值
    // b = 10;       // 非法：b 是常量
    const int* pb = &b; // 合法：依然可以对常量左值取地址

    std::string firstName = "Yan";
    PringName(firstName);
    std::string lastName = "Chernikov";
    PringName(lastName);
    std::string fullName = firstName + " " + lastName;
    PringName(firstName + " " + lastName);
    PringName(std::move(fullName));
    return 0;
}
