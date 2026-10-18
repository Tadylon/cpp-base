#include <iostream>
#include <thread>
#include <future>
#include <memory>
#include <vector>
#include <functional>

int heavy_task(int n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return n * n;
}

// 完美的 my_async 实现
template<typename F, typename... Args>
auto my_async(F&& f, Args&&... args) {
    // 1. 推导返回值类型
    using ReturnType = std::invoke_result_t<F, Args...>;
    
    // 2. 创建 promise
    auto prom = std::make_shared<std::promise<ReturnType>>();
    auto fut = prom->get_future();
    
    // 3. 使用 std::forward 完美转发函数和参数，并用 C++14 的移动捕获把它们移入 Lambda
    // 这样哪怕参数是 std::unique_ptr 这种不可拷贝的对象也能正常工作
    std::thread([
        prom, 
        task = std::forward<F>(f), 
        ...bound_args = std::forward<Args>(args)
    ]() mutable {
        try {
            // std::invoke 是 C++17 提供的标准调用设施，能同时兼容普通函数、Lambda 和成员函数
            if constexpr (std::is_void_v<ReturnType>) {
                std::invoke(std::move(task), std::move(bound_args)...);
                prom->set_value(); // void 类型特化处理
            } else {
                prom->set_value(std::invoke(std::move(task), std::move(bound_args)...));
            }
        } catch (...) {
            prom->set_exception(std::current_exception());
        }
    }).detach(); // 为了演示简便暂用 detach，工业级需要自定义包裹类管理生命周期
    
    return fut; 
}

int main () {
    std::vector<std::future<int>> futures;

    for (int i = 0; i < 100; ++i) {
        // 修复：去掉了 std::launch::async，直接传入 Lambda
        futures.push_back(my_async([i]() {
            return heavy_task(i); 
        }));
    }

    for (int i = 0; i < 100; ++i) {
        std::cout << "Task " << i << " result: " << futures[i].get() << std::endl;
    }

    return 0;
}