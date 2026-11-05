
```txt
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
```