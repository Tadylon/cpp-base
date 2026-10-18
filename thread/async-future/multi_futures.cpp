#include <thread>
#include <future>
#include <iostream>
#include <vector>

int heavy_task(int n) { 
    // 故意加个 sleep 模拟 I/O 或复杂计算
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    return n * n; 
}


int main() {
    std::vector<std::future<int>> futures;
    for (int i = 0; i < 100; ++i) {
        // 显式指定 async 策略，强制创建新线程
        futures.push_back(std::async(std::launch::async, heavy_task, i));
    }
    int sum = 0; 
    for (auto &f : futures) {
        sum += f.get(); // 阻塞获取
    }
    std::cout << "the result is : " << sum << std::endl;
    std::cin.get();
    return 0;
}
