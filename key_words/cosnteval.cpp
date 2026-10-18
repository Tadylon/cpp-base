#include <iostream>
#include <vector>


#include "print_obj.h"


consteval int square(int x) { return x * x; }

constexpr int square(int x , int y) { 
    return x * x + y * y; 
}
int get_input() { 
    return 23;
}

int main()
{

    int y = square(5);   // 合法
    cout__(y);
    int z = square(get_input(),get_input()); // 编译报错！因为输入是运行时获取的
    cout__(z);
    return 0;
}