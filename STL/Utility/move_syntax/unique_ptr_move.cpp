#include <iostream>
#include <memory>
#include <vector>
#include <assert.h>

#include "standard_time.h"
#include "print_obj.h"


int main()
{
    std::unique_ptr<int> ptr1 = std::make_unique<int>(10);
    // assert(std::unique_ptr<int> ptr2 = ptr1);          // 错误！unique_ptr不可拷贝
    // std::unique_ptr<int> ptr3 = std::move(ptr1); // 正确！所有权转移，ptr1变为nullptr
    auto ptr3 = std::move(ptr1); // 正确！所有权转移，ptr1变为nullptr

    std::vector<std::string> src = {"a", "b", "c"};
    std::vector<std::string> dst;
    // 将src中的所有字符串移动到dst，避免拷贝
    std::move(src.begin(), src.end(), std::back_inserter(dst));
    // 此时 src 中的字符串处于“有效但未指定”的状态（通常是空）
    PrintContainer(src);
    PrintContainer(dst);
    return 0;
}















