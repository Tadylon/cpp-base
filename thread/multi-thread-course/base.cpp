#if 1
// #define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<chrono>
#include<future>
#include<exception>
#include<stdexcept>

int task(int number)
{
    throw std::runtime_error("error ! ");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 100 + number;
}


void test()
{
    // 下面代码执行完成之后，异步任务就开始执行
    std::future<int> fut = std::async(std::launch::async, task, 10);
    std::cout << "the work start ..." << std::endl;

    try
    {
        // 阻塞等待任务函数执行结束，并得到结果
        int ret = fut.get();
        std::cout << "ret = " << ret << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        // return;
    }

    std::cout << "the work end ! " << std::endl;
}


int main()
{
    test();
    return EXIT_SUCCESS;
}
#endif