#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <cstdint>
#include <cstddef>
#include <type_traits>

template<typename T>
requires std::is_arithmetic_v<T> && (!std::is_same_v<std::remove_cv_t<T>, bool>)
void test()
{
    
}















