#include <iostream>
#include <csignal>
#include <chrono>
#include <thread>
#include <atomic>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>     // Linux/macOS 的 sleep
    #include <csignal>
#endif

std::atomic<bool> g_running(true);
void signalHandler( int signum )
{
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    exit(signum);  
}

// 跨平台的毫秒级休眠函数
void sleepMillis(int milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);  // usleep 单位是微秒
#endif
}

int main ()
{
    // 注册信号 SIGINT 和信号处理程序
    signal(SIGINT, signalHandler);  

    while(g_running){
    std::cout << "Going to sleep...." << std::endl;
    // std::this_thread::sleep_for(std::chrono::microseconds(1000));
    sleepMillis(1000);
    }

    while (g_running) {
        std::cout << "Going to sleep" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}