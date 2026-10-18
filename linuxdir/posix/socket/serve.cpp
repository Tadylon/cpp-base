#include <iostream>
#include <string>

#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "print_obj.h"

int main()
{
    // 1. 创建 socket
    int sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
    {
        printf("create socket error: errno=%d errmsg=%s\n", errno, strerror(errno));
        return 1;
    }
    else
    {
        printf("create socket success!\n");
    }

    // 2. 绑定 socket
    std::string ip = "127.0.0.1";
    int port = 8080;

    struct sockaddr_in sockaddr;
    std::memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);
    if (::bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        printf("socket bind error: errno=%d, errmsg=%s\n", errno, strerror(errno));
        return 1;
    }
    else
    {
        printf("socket bind success: ip=%s port=%d\n", ip.c_str(), port);
    }

    // 3. 监听 socket
    if (::listen(sockfd, 1024) < 0)
    {
        printf("socket listen error: errno=%d errmsg=%s\n", errno, strerror(errno));
        return 1;
    }
    else
    {
        printf("socket listen ...\n");
    }

    while (true)
    {
        // 4. 接收客户端连接
        int connfd = ::accept(sockfd, nullptr, nullptr);
        if (connfd < 0)
        {
            printf("socket accept error: errno=%d errmsg=%s\n", errno, strerror(errno));
            return 1;
        }

        char buf[1024] = {0};
        cout__(buf);
        // 5. 接收客户端的数据
        size_t len = ::recv(connfd, buf, sizeof(buf), 0);
        printf("recv: conn=%d msg=%s\n", connfd, buf);

        // 6. 向客服端发送数据
        ::send(connfd, buf, len, 0);
    }

    // 7. 关闭 socket
    ::close(sockfd);
    return 0;
}