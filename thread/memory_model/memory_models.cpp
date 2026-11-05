#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <cstdio>
#include <cstddef>


int main()
{

    std::atomic<int> a = 0;
    std::atomic<int> b = 0;
    int x = 0;
    int y = 0;
    std::thread th1([&](){
        a.store(1,std::memory_order_release);
        y = b.load();
    });

    std::thread th2([&](){
        b.store(1,std::memory_order_release);
        y = a.load();
    });
    
    th1.join();
    th2.join();
// std::memory_order
    std::cout << "x= "<< x << "  y= " << y << std::endl;
    return 0;
}
