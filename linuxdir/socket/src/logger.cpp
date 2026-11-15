#include "yazi/logger.h"

#include <cstdio>
#include <vector>

namespace yazi::log{

Logger::Logger(const std::string& path)
    : m_file(path, std::ios::out | std::ios::app)  // 若想覆盖用 std::ios::trunc
{
    // 可选：打开失败时的处理
    // if (!m_file.is_open()) { /* 记录到 stderr 或抛异常 */ }
}

// ---------------- 可变参数 -> std::string ----------------
std::string Logger::vformat(const char* fmt, va_list args) {
    // 1) 先拷贝一份，保证 args 还能再用一次
    va_list args_copy;
    va_copy(args_copy, args);

    // 2) 尝试用栈缓冲（绝大多数日志行都很短，免堆分配）
    char stack_buf[1024];
    int n = std::vsnprintf(stack_buf, sizeof(stack_buf), fmt, args_copy);
    va_end(args_copy);

    if (n < 0) {
        // 格式化失败（极少见，一般编码问题）
        return {};
    }

    if (static_cast<std::size_t>(n) < sizeof(stack_buf)) {
        // 未截断：直接返回
        return std::string(stack_buf, static_cast<std::size_t>(n));
    }

    // 3) 缓冲区不够，用记录的长度重新格式化（此时用原始 args）
    std::vector<char> heap_buf(static_cast<std::size_t>(n) + 1);
    std::vsnprintf(heap_buf.data(), heap_buf.size(), fmt, args);
    return std::string(heap_buf.data(), static_cast<std::size_t>(n));
}

// ---------------- 统一写入 ----------------
void Logger::write_line(const char* prefix, const char* fmt, va_list args) {
    if (!m_file.is_open()) return;

    if (prefix) m_file << prefix;
    m_file << vformat(fmt, args) << '\n';
    m_file.flush();   // 等价于原 fflush；要批量刷盘可改为条件 flush
}

// ---------------- 对外接口 ----------------
void Logger::log(const char* fmt, ...) {
    if (!m_file.is_open()) return;
    va_list args;
    va_start(args, fmt);
    write_line(nullptr, fmt, args);
    va_end(args);
}

void Logger::info(const char* fmt, ...) {
    if (!m_file.is_open()) return;
    va_list args;
    va_start(args, fmt);
    write_line("[INFO] ", fmt, args);
    va_end(args);
}

void Logger::error(const char* fmt, ...) {
    if (!m_file.is_open()) return;
    va_list args;
    va_start(args, fmt);
    write_line("[ERROR] ", fmt, args);
    va_end(args);
}

}