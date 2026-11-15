#pragma once

#include <fstream>
#include <string>
#include <cstdarg>

namespace yazi::log {


// 优雅的现代 C++ 单例 Logger
// class Logger {
// public:
//     // 提供全局唯一访问点
//     static Logger* instance() {
//         static Logger inst; // 局部静态变量，线程安全且只初始化一次
//         return &inst;
//     }

//     ~Logger();

//     bool open(const char* filename);
//     void log(const char* format, ...);
//     void error(const char* format, ...);
//     void info(const char* format, ...);

//     // 禁用拷贝构造和赋值
//     Logger(const Logger&) = delete;
//     Logger& operator=(const Logger&) = delete;
//     Logger(const Logger&&) = delete;
//     Logger&& operator=(const Logger&&) = delete;

// private:
//     std::fstream m_file;
//     Logger() = default; // 私有构造函数
// };



class Logger {
public:
    explicit Logger(const std::string& path);

    void log  (const char* fmt, ...);
    void info (const char* fmt, ...);
    void error(const char* fmt, ...);

private:
    std::ofstream m_file;

    // 把可变参数格式化成 std::string
    static std::string vformat(const char* fmt, va_list args);

    // 统一写入逻辑：前缀 + 内容 + 换行 + flush
    void write_line(const char* prefix, const char* fmt, va_list args);
};















}