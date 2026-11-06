

## type_traits

它的核心能力是：在编译期检查、分析、修改和转换类型的属性。换言之，它把“类型”当成数据，让编译器在编译阶段对其进行内省和计算，从而实现静态分发、条件编译和严格的类型约束。


### `std::integral_constant`
标准库中绝大多数产生值的 trait（比如 is_integral）都继承自 std::integral_constant
```cpp
template <class T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

// 预定义布尔常量别名
using true_type  = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;
```




## Categories
分类

### Primary Type Categories

基础类型分类

这些 trait 互斥，每个类型必然且只属于其中一种：

```cpp
is_void<T>

is_null_pointer<T>

is_integral<T>

is_floating_point<T>

is_array<T>

is_pointer<T>

is_reference<T>

is_enum<T>

is_union<T>

is_class<T>

is_function<T>
```


### Composite & Properties
复合类型与类型属性

复合检查： is_arithmetic<T>（整型或浮点）、is_scalar<T>（标量）、is_object<T> 等。

修饰符检查： is_const<T>、is_volatile<T>、is_signed<T>、is_unsigned<T>。


生命周期与能力检查：

构造与析构：is_default_constructible<T>、is_copy_constructible<T>、is_move_constructible<T>、is_destructible<T>。

赋值操作：is_copy_assignable<T>、is_move_assignable<T>。

异常安全性：is_nothrow_move_constructible<T>（对于 std::vector 扩容时是否调用移动构造至关重要）。

内存布局特性：is_trivial<T>、is_standard_layout<T>、is_trivially_copyable<T>（判断能否使用 memcpy）。


### Type Relationships
类型关系判断

is_same<T, U>：两个类型是否完全一致（包含顶层 const/引用匹配）。

is_base_of<Base, Derived>：是否构成基类与派生类关系。

is_convertible<From, To>：From 是否可以隐式转换为 To。

is_invocable<Fn, Args...>（C++17）：函数对象 Fn 是否可用参数 Args... 调用


### Type Transformations
类型转换与修饰移除

引用修饰： remove_reference<T>、add_lvalue_reference<T>、add_rvalue_reference<T>。

常量修饰： remove_const<T>、add_const<T>、remove_cv<T>。

指针修饰： remove_pointer<T>、add_pointer<T>。

衰减（Decay）： decay<T>（模拟传值调用时的隐式转换：数组转指针、函数转函数指针、去除顶层 const 和引用）。

复合修饰： remove_cvref<T>（C++20，相当于 remove_cv_t<remove_reference_t\<T>>）。


## Syntax sugar

`_v` 与 `_t`

```cpp
typename std::remove_reference<T>::type a; // 获取类型
bool b = std::is_integral<T>::value;        // 获取值
```

### `_t`

```cpp
std::remove_reference_t<T> a;
std::decay_t<T> b;
```


### `_v`

```cpp
bool is_int = std::is_integral_v<T>;
bool same = std::is_same_v<T, int>;
```




