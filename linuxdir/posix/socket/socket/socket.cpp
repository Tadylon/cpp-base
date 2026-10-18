#include "socket.h"
#include <cstdio>
#include <cstdarg>
#include <unistd.h>

namespace yazi {
namespace socket {

// ============ Socket 实现 ============
Socket::Socket() {
    m_sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (m_sockfd < 0) {
        perror("socket");
        // 你可以选择抛出异常或记录日志
    }
}

Socket::Socket(int fd) : m_sockfd(fd) {
    // 用于 accept 返回的客户端 fd
}

Socket::~Socket() {
    close();
}

int Socket::fd() const {
    return m_sockfd;
}

void Socket::bind(const char* ip, int port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (ip == nullptr || strcmp(ip, "0.0.0.0") == 0) {
        addr.sin_addr.s_addr = INADDR_ANY;
    } else {
        inet_pton(AF_INET, ip, &addr.sin_addr);
    }

    if (::bind(m_sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        // 处理错误
    }
}

void Socket::listen(int backlog) {
    if (::listen(m_sockfd, backlog) < 0) {
        perror("listen");
    }
}

int Socket::accept() {
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int client_fd = ::accept(m_sockfd, (struct sockaddr*)&client_addr, &len);
    if (client_fd < 0) {
        perror("accept");
        return -1;
    }
    return client_fd;
}

ssize_t Socket::send(const char* buf, size_t len) {
    return ::send(m_sockfd, buf, len, 0);
}

ssize_t Socket::recv(char* buf, size_t len) {
    return ::recv(m_sockfd, buf, len, 0);
}

void Socket::close() {
    if (m_sockfd >= 0) {
        ::close(m_sockfd);
        m_sockfd = -1;
    }
}

// ============ Logger 实现 ============
Logger::~Logger() {
    if (m_file) {
        fclose(m_file);
        m_file = nullptr;
    }
}

bool Logger::open(const char* filename) {
    if (m_file) {
        fclose(m_file);
        m_file = nullptr;
    }
    m_file = fopen(filename, "a");   // 追加模式
    if (!m_file) {
        perror("fopen");
        return false;
    }
    return true;
}

void Logger::log(const char* fmt, ...) {
    if (!m_file) return;
    va_list args;
    va_start(args, fmt);
    vfprintf(m_file, fmt, args);
    fprintf(m_file, "\n");
    fflush(m_file);   // 确保立即写入
    va_end(args);
}

void Logger::error(const char* fmt, ...) {
    if (!m_file) return;
    va_list args;
    va_start(args, fmt);
    fprintf(m_file, "[ERROR] ");
    vfprintf(m_file, fmt, args);
    fprintf(m_file, "\n");
    fflush(m_file);
    va_end(args);
}

void Logger::info(const char* fmt, ...) {
    if (!m_file) return;
    va_list args;
    va_start(args, fmt);
    fprintf(m_file, "[INFO] ");
    vfprintf(m_file, fmt, args);
    fprintf(m_file, "\n");
    fflush(m_file);
    va_end(args);
}

} // namespace socket
} // namespace yazi