#include <iostream>
#include <exception>
#include <new>
#include <typeinfo>
#include <optional>
#include <stdexcept> // 包含标准异常类
#include <system_error>

/*
[头文件 <exception>]
        |
        +-- std::exception  (基类，定义 what())
                |
                +-- std::bad_alloc      (在 <new> 中定义)
                +-- std::bad_cast       (在 <typeinfo> 中定义)
                +-- std::bad_typeid     (在 <typeinfo> 中定义)
                +-- std::bad_optional_access (在 <optional> 中)
                +-- ==========================================
                |   [头文件 <stdexcept>] 从这里开始
                +-- std::logic_error
                |       +-- invalid_argument
                |       +-- domain_error
                |       +-- length_error
                |       +-- out_of_range
                +-- std::runtime_error
                        +-- range_error
                        +-- overflow_error
                        +-- underflow_error
                        +-- system_error  (在 <system_error> 中)
*/


int main() {
    try {
        // 1. 可能抛出异常的代码
        throw std::runtime_error("something wrong happend in run time !");
        // 如果抛出异常，这之后的代码将不会执行
    }
    catch (const std::runtime_error& e) { // 2. 捕获特定类型的异常
        // 3. 处理异常
        std::cerr << "catch runtime_error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) { // 4. 捕获更通用的异常
        std::cerr << "catch standard error: " << e.what() << std::endl;
    }
    catch (...) { // 5. 捕获所有其他类型的异常
        std::cerr << "catch unknown error: " << std::endl;
    }
    
    std::cout << "the program is runing again !" << std::endl;
    
    auto return_msg = std::invalid_argument("something gets wrong !");
    auto return_msg2 = std::logic_error("no ways !");

    return 0;
}