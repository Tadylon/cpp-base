#include <generator>
#include <iostream>
#include <cstdint>
#include <ranges>

// namespace std {
//     template<class Ref, class V = void, class Allocator = void>
//     class generator : public ranges::view_interface<generator<Ref, V, Allocator>>;
// }

std::generator<uint64_t> fibonacci()
{
    uint64_t a = 0;
    uint64_t b = 1;
    while (true) {
        co_yield a;
        auto next = a + b;
        a = b;
        b = next;
    }
}

int main(int argc, char** argv)
{
    auto pipeline = fibonacci()
                | std::views::filter([](uint64_t x) {return x%2 == 0;})
                | std::views::drop(2)
                | std::views::take(5);
    
    std::cout << "Eligible Fibonacci even numbers: ";
    for (uint64_t num  : pipeline) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    return 0;
}
