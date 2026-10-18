#include <iostream>
#include <thread>
#include <chrono>
#include <stop_token>

void worker(std::stop_token stoken) {
    // 检查停止请求
    while (!stoken.stop_requested()) {
        std::cout << "Working..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "Worker stopped gracefully" << std::endl;
}


int main() {
    std::jthread t(worker);  // 自动传递 stop_token
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // 请求线程停止
    t.request_stop();
    
    // 析构时自动 join，等待 worker 清理完毕
    return 0;
}