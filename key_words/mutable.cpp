#include <iostream>
#include <string>


class Foo {
public:
    mutable int counter_ = 0;   // 合法：非静态、非 const
    // mutable static int s;    // 非法：不能用于 static 成员
    // mutable const int c = 0; // 非法：成员本身不能是 const
};



int main()
{
    const Foo f;
    int* p = &f.counter_;  // 合法，因为 counter_ 是 mutable
    return 0;
}

