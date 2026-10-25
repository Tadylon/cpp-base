#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "print_obj.h"

template <class T, class Allocator = std::allocator<T>>
class vector;

template <class T>
struct MyAllocator : public std::allocator<T> {
    T* allocate(size_t n) {
        // 自定义分配逻辑（例如从池中取）
        return std::allocator<T>::allocator;
    }
    void deallocate(T* p, size_t n) {
        std::allocator<T>::deallocate(p, n);
        // 自定义释放逻辑
    }
};

using Vec = std::vector<int, MyAllocator<int>>;

int main()
{

    return 0;
}