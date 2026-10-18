#include <cassert>
#include <array>
#include <iostream>
#include <vector>
#include <type_traits>


#include "print_obj.h"
#include "standard_time.h"

constexpr double PI = 3.1415926;
constexpr int MAX_SIZE = 1024;

constexpr int square(auto x) { return x * x; }

int common_square(int x) {
    return x * x;
}

// C++14 及以后，可以写复杂逻辑
constexpr int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

template<typename T>
void print_type(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "int : " << value << "\n";
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "float : " << value << "\n";
    } else {
        std::cout << "other types \n";
    }
}
// 当 T=int 时，浮点和 else 分支的代码根本不会被编译器生成！
// 这比运行时 if 要高效，并且允许在分支内调用针对特定类型才有的函数。


// C++20 合法代码
constexpr std::vector<int> get_numbers() {
    std::vector<int> v_get_num{1, 2, 3};
    v_get_num.push_back(4);
    return v_get_num; // 注意：这个 vector 在编译期存在，编译期结束后内存被销毁，只保留最终结果
}

constexpr std::array<int, 4> get_numbers_c17() {
    return {1, 2, 3, 4}; // 注意：没有 push_back，编译期直接构造字面量
}


int main() {
    std::cout << "C++ Standard: " << __cplusplus << std::endl;

    int arr[square(5)];  // C++ 中数组大小必须是编译期常量
    {
        Timer timer("constexpr");
        for (int i =0; i < 10000; ++i) {
            int test = square(5); 
            //在编译时被计算为 25，完全等价于 int arr[25];
        }
    }
    {
        Timer timer("common const : ");
        for (int u =0; u < 10000; ++u) {
            int test = common_square(5); 
            //在编译时被计算为 25，完全等价于 int arr[25];
        }
    }
    


    cout__("---------------------------------\n");
    int x = 10;
    const int a = x;        // 合法，a 是运行时常量（只读）
    
    // 编译错误！x 不是编译期常量
    // constexpr int b = x;    
    
    constexpr int c = 10;   // 合法，10 是字面量
    const int d = 10;       // 合法，但 d 只是只读变量，不保证编译期存在
    
    cout__("---------------------------------\n");
    cout__("marco and template : ");
    
    
    std::array<int, MAX_SIZE> arr_data; // 完美适配模板参数
    // PrintContainer(arr_data);
    
    cout__("---------------------------------\n");
    cout__("complex logical : ");
    
    {
        Timer timer_assert("static_assert in constexpr : ");
        static_assert(factorial(5) == 120); // 编译期断言，绝对零开销
        int arr_assert[factorial(4)];               // arr 大小为 2
    }
    
    cout__("---------------------------------\n");
    cout__("if fenzhi exception : ");
    print_type(d);
    std::string type_except = "hello xixi";
    print_type(type_except);


    
    constexpr auto static v_get = get_numbers_c17(); // 编译期构造
    static_assert(v_get[0] == 1); // 编译期验证
    return 0;
}