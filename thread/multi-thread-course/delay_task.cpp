#include<iostream>
#include<thread>
#include<chrono>
#include<future>


int task(int number)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 100 + number;
}

void test01()
{
    // 任务不会马上执行
    std::future<int> fut = std::async(std::launch::deferred, task, 10);

    // 当调用 get、wait 函数时，触发任务函数执行
    fut.wait();
    int ret = fut.get();
    std::cout << "ret = " << ret << std::endl;
}


void test02()
{
    std::future<int> fut = std::async(std::launch::deferred, task, 10);
    bool is_start = false;

    while (true)
    {
        // 当延迟任务尚未执行前，wait_for 函数不会阻塞，会立即返回
        std::future_status status = fut.wait_for(std::chrono::seconds(1));

        if (status == std::future_status::deferred && !is_start)
        {
            std::cout << "the task hasn`t finished ..." << std::endl;
            std::thread([&fut]() { fut.wait(); }).detach();
            is_start = true;
        }

        if (status == std::future_status::timeout)
        {
            std::cout << "the task is running ..." << std::endl;
        }

        if (status == std::future_status::ready)
        {
            std::cout << "the task is finished , the result is : " << fut.get() << std::endl;
            break;
        }
    }
}


int main()
{

    test01();
    std::cout << "the test01 has finished ! " << std::endl;
    test02();
    return EXIT_SUCCESS;
}