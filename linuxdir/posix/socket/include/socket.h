#pragma once
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdarg>

namespace yazi 
{
    namespace socket 
    {
        class Socket {
        public:
            Socket();

            Socket(int fd);
            
            ~Socket();
            
            int fd() const;
            void bind(const char* ip, int port);
            void listen(int backlog);
            int accept();
            ssize_t send(const char* buf, size_t len);
            ssize_t recv(char* buf, size_t len);
            void close();

        protected:
            std::string m_ip;
            int m_port;
            int m_sockfd;
        private:
            int m_fd;
        };

// 优雅的现代 C++ 单例 Logger
    class Logger {
    public:
        // 提供全局唯一访问点
        static Logger* instance() {
            static Logger inst; // 局部静态变量，线程安全且只初始化一次
            return &inst;
        }

        ~Logger();

        bool open(const char* filename);
        void log(const char* format, ...);
        void error(const char* format, ...);
        void info(const char* format, ...);

        // 禁用拷贝构造和赋值
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

    private:
        FILE* m_file = nullptr;
        Logger() = default; // 私有构造函数
    };

    }
}