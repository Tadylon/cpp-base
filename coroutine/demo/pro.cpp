#include <iostream>
#include <coroutine>

// 自定义一个 Awaiter：模拟异步读取一个整数
struct AsyncReadData {
    int simulated_data;

    // 1. 检查是否就绪：返回 false 强制触发挂起流程
    bool await_ready() const noexcept {
        std::cout << "    [Awaiter] 1. await_ready(): 数据还没好，准备挂起协程...\n";
        return false;
    }

    // 2. 协程已挂起，编译器把当前协程的句柄 h 传进来
    void await_suspend(std::coroutine_handle<> h) const noexcept {
        std::cout << "    [Awaiter] 2. await_suspend(): 协程已挂起！拿到句柄，可以在这里把 h 交给异步 I/O 线程\n";
        // 在真实异步框架（如 Boost.Asio）中，这里会注册回调，等 I/O 完成后调用 h.resume()
        // 为了演示极简流程，我们在这里直接立刻恢复它：
        std::cout << "    [Awaiter]    ---> 假装 I/O 完成了，立刻调用 h.resume() 唤醒协程！\n";
        h.resume();
    }

    // 3. 协程恢复后立即执行，返回值作为 co_await 表达式的结果
    int await_resume() const noexcept {
        std::cout << "    [Awaiter] 3. await_resume(): 协程已醒来，将结果返回给 co_await 左侧变量\n";
        return simulated_data;
    }
};

// 极简的空壳 Task 返回类型
struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; } // 创建后立即执行，不挂起
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

Task my_async_coroutine() {
    std::cout << "  [协程] 开始执行，发起 co_await 异步读取...\n";
    
    // 核心：co_await 会依次触发 await_ready -> await_suspend -> await_resume
    int result = co_await AsyncReadData{42}; 
    
    std::cout << "  [协程] 成功拿到 co_await 的返回值: " << result << "\n";
}

int main() {
    std::cout << "[Main] 启动协程\n";
    my_async_coroutine();
    std::cout << "[Main] 结束\n";
    return 0;
}