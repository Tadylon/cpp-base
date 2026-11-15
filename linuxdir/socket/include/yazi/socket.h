#pragma once

#include <cstring>
#include <string>


namespace yazi::socket {


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

}
