#include<iostream>
#include<thread>
#include<chrono>
#include<future>


void test()
{
    std::future<int> fut = std::async(std::launch::deferred, []() {
        std::cout << "the dalay task is running ..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 100;
    });

#if 0
    // std::future 只能获取一次结果，重复获取结果将会抛出异常
    // std::shared_future 可以重复获取结果
    int ret = fut.get();
    ret = fut.get();
#else
    std::shared_future<int> shared_fut = fut.share();
    int ret = shared_fut.get();
    ret = shared_fut.get();
#endif
}


int main()
{
    test();
    return EXIT_SUCCESS;
}
