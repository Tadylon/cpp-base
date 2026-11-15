#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>

bool send_all(int sock, const char* data, size_t len) {
    size_t total = 0;
    while (total < len) {
        ssize_t sent = send(sock, data + total, len - total, MSG_NOSIGNAL); // 防止SIGPIPE
        if (sent <= 0) {
            perror("send failed");
            return false;
        }
        total += sent;
    }
    return true;
}

int main() {
    signal(SIGPIPE, SIG_IGN); // 全局忽略

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("socket");
        return -1;
    }

    // 设置收发超时（5秒）
    struct timeval tv = {5, 0};
    setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(clientSocket, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    // 修正：使用具体IP
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid IP" << std::endl;
        close(clientSocket);
        return -1;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("connect");
        close(clientSocket);
        return -1;
    }

    const char* message = "Hello, server!";
    if (!send_all(clientSocket, message, strlen(message))) {
        close(clientSocket);
        return -1;
    }

    // 优雅关闭写入端
    shutdown(clientSocket, SHUT_WR);

    // 读取服务器响应（直到对方关闭）
    char buffer[1024];
    while (true) {
        ssize_t n = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (n > 0) {
            buffer[n] = '\0';
            std::cout << "Server response: " << buffer << std::endl;
        } else if (n == 0) {
            std::cout << "Server closed connection gracefully." << std::endl;
            break;
        } else {
            perror("recv error");
            break;
        }
    }

    close(clientSocket);
    return 0;
}