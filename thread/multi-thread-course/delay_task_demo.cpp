#include<iostream>
#include<thread>
#include<chrono>
#include<future>
#include<map>


std::string data_analysis(std::string path)
{
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return path;
}


void test()
{

    std::map<std::string, std::tuple<bool, std::shared_future<std::string>>> tasks;

    // 添加延迟图像处理任务
    tasks.insert({ "a.png", {false, std::async(std::launch::deferred, data_analysis, "a.png")} });
    tasks.insert({ "b.png", {false, std::async(std::launch::deferred, data_analysis, "b.png")} });
    tasks.insert({ "c.png", {false, std::async(std::launch::deferred, data_analysis, "c.png")} });

    // 用户查看图像
    std::string name;
    while (true)
    {
        std::cout << "please input the picture you want to see : ";
        std::cin >> name;

        if (name == "exit")
        {
            for (auto& task : tasks)
            {
                std::cout << task.first << " " << std::boolalpha << std::get<0>(task.second) << std::endl;
            }
            std::cout << "----------------" << std::endl;
            break;
        }

        // 查看图像目前状态
        auto& picture = tasks[name];
        auto& is_ok = std::get<0>(picture);
        auto& fut = std::get<1>(picture);

        if (is_ok)
        {
            std::cout << "the picture you want to see : " << fut.get() << std::endl;
            continue;
        }

        std::future_status status = fut.wait_for(std::chrono::seconds(1));

        if (status == std::future_status::deferred)
        {
            std::cout << "the process of dealing with pictures hasn`t start ..." << std::endl;
            std::thread([&fut]() { fut.wait(); }).detach();
        }

        if (status == std::future_status::timeout)
        {
            std::cout << "the deal with picture is running ! " << std::endl;
        }

        if (status == std::future_status::ready)
        {
            is_ok = true;
        }

        std::cout << "----------------" << std::endl;
    }
}


int main()
{
    test();
    return EXIT_SUCCESS;
}