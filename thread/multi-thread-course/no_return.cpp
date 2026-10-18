#if 1
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<chrono>
#include<future>
#include<fstream>
#include <cstdlib>

void write_file(std::string filename, std::string content)
{
    std::ofstream ofs(filename);

    // 等待 2 秒，表示耗时任务
    std::this_thread::sleep_for(std::chrono::seconds(2));

    ofs << content << std::endl;
    ofs.close();
}


void test()
{
    // 下面代码执行完成之后，线程函数就开始执行
    std::future<void> fut1 = std::async(std::launch::async, write_file, "demo1.txt", "hello world");
    std::future<void> fut2 = std::async(std::launch::async, write_file, "demo2.txt", "hello python");
    std::cout << "the work start ..." << std::endl;

    // 等待异步任务执行完毕
    fut1.wait();
    fut2.wait();

    // 合并文件
    std::ifstream ifs1("demo1.txt");
    std::ifstream ifs2("demo2.txt");
    std::ofstream ofs("demo.txt");

    std::copy(std::istreambuf_iterator<char>(ifs1), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(ofs));
    std::copy(std::istreambuf_iterator<char>(ifs2), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(ofs));

    ifs1.close();
    ifs2.close();
    ofs.close();

    std::cout << "the work end ! " << std::endl;
}


int main()
{
    test();
    return EXIT_SUCCESS;
}
#endif