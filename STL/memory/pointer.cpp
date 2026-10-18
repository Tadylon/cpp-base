#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>


void uniquePointerDemo() {
    // 使用 std::make_unique 是最安全、最高效的方式 (C++14)
    auto p = std::make_unique<int>(100);

    // 正常使用，不需要手动 delete
    if (*p > 50) {
        return; // 哪怕这里直接返回，p 也会在函数结束时自动销毁
    }
} // 作用域结束，内存自动释放


void sharedPointerDemo() {
    // auto p1 = std::make_shared<int>(200);
    std::shared_ptr<int> p1 = std::make_shared<int>(200);
    {
        std::shared_ptr<int> p2 = p1; // 引用计数变为 2
        // auto p2 = p1; // 引用计数变为 2
        
        // p1 和 p2 指向同一块内存
    } // p2 离开作用域，引用计数变回 1，内存不释放
} // p1 离开作用域，引用计数变 0，内存释放



