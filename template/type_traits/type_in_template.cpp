#include <type_traits>
#include <concepts>
#include <iostream>
#include <utility>
#include <memory>

template <typename T>
struct is_copy_constructible_helper {
private:
    template <typename U, typename = decltype(U(std::declval<const U&>()))>
    static std::true_type test(int);

    template <typename>
    static std::false_type test(...);

public:
    using type = decltype(test<T>(0));
};

template <typename T>
struct is_copy_constructible : is_copy_constructible_helper<T>::type {};