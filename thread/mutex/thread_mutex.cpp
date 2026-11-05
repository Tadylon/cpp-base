#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

static int nomtx_counter = 0;
static int withmtx_counter = 0;

std::mutex mtx;

void increase_counter_no_mutex() {

    for (int i = 0; i < 1'000'000; ++i) {
        ++nomtx_counter; // 没有任何保护，多线程同时读写
    }
}

void increase_counter_with_mutex() {

    std::lock_guard<std::mutex> lock(mtx);
    // mtx.lock();
    for (int i = 0; i < 1'000'000; ++i) {
        ++withmtx_counter; // 没有任何保护，多线程同时读写
    }
    // mtx.unlock();
}

void test_no_mutex() {
    std::vector<std::thread> threads1;
    for (int i = 0; i < 10; ++i) {
        threads1.emplace_back(increase_counter_no_mutex);
    }
    for (auto& t : threads1) t.join();
    
    // 理论上应该是 1000000 (100万)
    // 但实际运行你会发现结果是一个随机的、小于 100 万的数字
    std::cout << "Final counter: " << nomtx_counter << std::endl; 
}

void test_with_mutex() {
    std::vector<std::thread> threads2;
    for (int i = 0; i < 10; ++i) {
        threads2.emplace_back(increase_counter_with_mutex);
    }
    for (auto& t : threads2) t.join();

    //这里输出出来的内容就应该是正常数值，因为加入了mutex
    std::cout << "Final counter: " << withmtx_counter << std::endl; 
}


int main() {
    test_no_mutex();
    test_with_mutex();
    return 0;
}