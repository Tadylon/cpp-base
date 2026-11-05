

C++ 流类的命名非常规律，可以拆成三部分：

```txt
[方向前缀] + [设备] + stream
```

ifstream = 文件输入流（读文件）

ofstream = 文件输出流（写文件）

fstream = 文件双向流（读写文件）

istringstream = 字符串输入流（从字符串读）

ostringstream = 字符串输出流（写到字符串）

stringstream = 字符串双向流（读写字符串）

```txt
std::ios_base                    ← 格式标志、异常设置
   └── std::basic_ios<CharT>     ← 状态标志、缓冲区指针
          ├── std::basic_istream<CharT>   （输入能力：>>, getline, read）
          │      ├── std::basic_ifstream<CharT>
          │      └── std::basic_istringstream<CharT>
          ├── std::basic_ostream<CharT>   （输出能力：<<, put, write）
          │      ├── std::basic_ofstream<CharT>
          │      └── std::basic_ostringstream<CharT>
          └── std::basic_iostream<CharT>  （同时继承 istream 和 ostream）
                 ├── std::basic_fstream<CharT>
                 └── std::basic_stringstream<CharT>
```
i/o 前缀决定你能调用哪些接口。ofstream 继承 ostream，所以它没有 >>；ifstream 继承 istream，所以它没有 <<。

fstream 和 stringstream 是“兄弟”关系，它们都继承 iostream，接口几乎一样，区别只在于底层绑定的“设备”是文件还是内存字符串。这正是它们可以互相替换使用（比如写一个接受 std::ostream& 的函数）的基础。


### fstream

三个类的默认打开模式

|类	|默认 openmode|	行为
|-|-|-|
ofstream|	out \| trunc	|文件不存在则创建；存在则清空
ifstream|	in	|文件不存在则失败
fstream	|in \| out	|文件不存在则失败，不会自动创建

openmode常用组合


模式	|含义
|-|-|
ios::in	|读
ios::out|	写（隐含 trunc，除非同时指定 app/ate）
ios::app|	所有写入追加到末尾
ios::ate|	打开后定位到末尾，但可继续读写
ios::trunc	|打开时清空文件
ios::binary	|二进制模式，不做换行转换


### stringstream

stringstream 把流接口和内存字符串结合起来，主要用于四类场景：

1. 数值 ↔ 字符串转换（类型安全地替代 atoi / sprintf）
2. 解析格式化字符串（把一行文本拆成多个字段）
3. 构建复杂字符串（拼接、对齐、进制/精度控制）
4. 在内存中模拟文件流（测试、序列化中间步骤）



维度	|fstream 家族|	stringstream 家族
|-|-|-|
底层设备|	磁盘文件|	内存中的 std::string
主要用途|	持久化、文件 I/O|	格式转换、解析、字符串构建
速度	|受磁盘 I/O 限制	|纯内存，通常更快
持久性	|数据写入磁盘|	进程结束即消失
接口	|与 stringstream 几乎相同|	与 fstream 几乎相同
异常配置|	exceptions(...)	|exceptions(...)
典型替代|	C 的 FILE*|	C 的 sprintf / sscanf / atoi


