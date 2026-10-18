#if 1
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<chrono>
#include<future>


int calculate(int number)
{
    int result = 0;
    for (int i = 0; i < number; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        result += 10;
    }

    return result;
}


void test()
{
    std::future<int> fut = std::async(std::launch::async, calculate, 10);
    std::cout << "start work ..." << std::endl;


    while (true)
    {
        std::future_status status = fut.wait_for(std::chrono::seconds(1));
        // std::future_status status = fut.wait_until(std::chrono::steady_clock().now() + std::chrono::seconds(2));
        if (status == std::future_status::ready)
        {
            std::cout << "the result of child thread is : " << fut.get() << std::endl;
            break;
        }

        if (status == std::future_status::timeout)
        {
            std::cout << "the child thread hasn`t finished ..." << std::endl;
        }
    }
}


int main()
{
    test();
    return EXIT_SUCCESS;
}
#endif