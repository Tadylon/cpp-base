

# requires


## Concept

直接表示（Requires Clause）：
当你的条件已经是现成的 bool 常量（比如 std::is_arithmetic_v<T> 或已定义好的 concept）时，直接跟在 requires 后面作为布尔条件过滤即可。

写成表达式的形式（Requires Expression）：
当你需要测试某段代码语法是否合法（比如是否支持 x + y、是否存在某个成员函数、是否重载了 <<）时，没有现成的 bool 变量能直接拿到，就必须开启一个测试块 requires(...) { ...; }。

## Use

### Requires Clause
requires 子句
$$\text{requires ...}$$

```cpp
template<typename T>
requires std::is_arithmetic_v<T> && (!std::is_same_v<std::remove_cv_t<T>, bool>)
void test(T t){}
```


### Requires Expression
requires 表达式

$$requires (\text{paraments}) \{ ... \}$$


1. 简单要求（Simple Requirements）

仅测试表达式在语法上是否可被编译（不会在运行时真正执行）。
```cpp
template<typename T>
concept Printable = requires(T x) {
    std::cout << x; // 测试：std::cout << x 这行代码能否合法编译
};
```

2. 类型要求（Type Requirements）

用关键字 typename 开头，测试某个关联类型或嵌套类型是否存在。

```cpp
template<typename T>
concept HasValueType = requires {
    typename T::value_type; // 测试：类型 T 内部是否有 using 或 typedef 定义的 value_type
};
```


3. 复合要求（Compound Requirements）

用大括号 { expr } 包裹表达式，后接可选的 noexcept 或返回类型约束 -> Concept：

```cpp
template<typename T>
concept Stringifiable = requires(T x) {
    // 测试：x.to_string() 必须合法，且其返回值必须满足 std::convertible_to<std::string>
    { x.to_string() } -> std::convertible_to<std::string>;
    
    // 测试：x.size() 必须是不抛出异常的 (noexcept)
    { x.size() } noexcept;
};
```

4. 嵌套要求（Nested Requirements）

在表达式内部再次使用 requires，用来引入额外的编译期常量布尔约束：

```cpp
template<typename T>
concept BigType = requires {
    requires sizeof(T) >= 8; // 嵌套要求：必须额外满足尺寸条件
};
```

