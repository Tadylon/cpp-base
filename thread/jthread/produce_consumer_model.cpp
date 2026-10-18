#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <stop_token>
#include <chrono>

// using namespace std;

class ThreadSafeQueue {
private:
    std::queue<int> q;
    std::mutex mtx;
    std::condition_variable_any cv;
    
public:
    void push(int value) {
        std::lock_guard<std::mutex> lock(mtx);
        q.push(value);
        cv.notify_one();
    }
    
    int pop(std::stop_token stoken) {
        std::unique_lock<std::mutex> lock(mtx);
        // wait 会自动响应停止请求
        cv.wait(lock, stoken, [this] {
            return !q.empty();
        });
        
        if (stoken.stop_requested() && q.empty()) {
            return -1;  // 停止信号
        }
        
        int value = q.front();
        q.pop();
        return value;
    }
};

int main() {
    ThreadSafeQueue queue;
    std::stop_source source;
    
    // 生产者
    std::jthread producer([&](std::stop_token st) {
        int count = 0;
        while (!st.stop_requested()) {
            queue.push(++count);
            std::cout << "Produced: " << count << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        std::cout << "Producer stopped" << std::endl;
    });
    
    // 消费者
    std::jthread consumer([&](std::stop_token st) {
        while (true) {
            int value = queue.pop(st);
            if (value == -1) break;  // 停止信号
            std::cout << "Consumed: " << value << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        std::cout << "Consumer stopped" << std::endl;
    });
    
    // 运行3秒后停止
    std::this_thread::sleep_for(std::chrono::seconds(3));
    source.request_stop();
    
    return 0;
}