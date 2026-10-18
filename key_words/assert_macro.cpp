// #define NDEBUG          // 加上这行，则 assert 不可用
#include <cassert>
#include <iostream>
#include <cstddef>

#define DEMO_ASSERT(expr) assert(expr)

int main()
{

    long p = 232;
    p = NULL;
    DEMO_ASSERT( p != NULL );    // assert 不可用
    std::cout << "p != NULL\n"; 
    return 0;
}