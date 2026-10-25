#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <type_traits>

class ThreadPool {
public:
    // 构造函数：创建指定数量的工作线程，默认使用硬件并发数
    explicit ThreadPool(size_t threads = std::thread::hardware_concurrency())
        : stop_(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers_.emplace_back([this] {
                // 工作线程的主循环
                for (;;) {
                    std::function<void()> task;
                    {
                        // 获取互斥锁，保护任务队列
                        std::unique_lock<std::mutex> lock(this->queue_mutex_);
                        // 条件变量等待：直到线程池停止或有新任务到来
                        this->condition_.wait(lock, [this] {
                            return this->stop_ || !this->tasks_.empty();
                        });
                        // 如果线程池已停止且任务队列为空，线程退出
                        if (this->stop_ && this->tasks_.empty())
                            return;
                        // 从队列取出一个任务
                        task = std::move(this->tasks_.front());
                        this->tasks_.pop();
                    } // 离开作用域，锁自动释放，在锁外执行任务
                    task(); // 执行任务
                }
            });
        }
    }

    // 提交任务：支持任意可调用对象和参数，返回一个 std::future 以便获取结果
    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::invoke_result_t<F, Args...>> {
        using return_type = typename std::invoke_result_t<F, Args...>;

        // 将任务打包成 packaged_task，以便自动获取返回值或异常
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            // 禁止向已停止的线程池提交任务
            if (stop_)
                throw std::runtime_error("enqueue on stopped ThreadPool");
            // 将任务包装为 void() 形式放入队列
            tasks_.emplace([task]() { (*task)(); });
        }
        condition_.notify_one(); // 唤醒一个工作线程
        return res;
    }

    // 析构函数：优雅地关闭线程池
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            stop_ = true;
        }
        condition_.notify_all(); // 唤醒所有线程
        for (std::thread& worker : workers_) {
            if (worker.joinable())
                worker.join(); // 等待每个线程执行完毕
        }
    }

    // 禁止拷贝
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

private:
    std::vector<std::thread> workers_;          // 工作线程集合
    std::queue<std::function<void()>> tasks_;   // 任务队列
    std::mutex queue_mutex_;                    // 保护任务队列的互斥锁
    std::condition_variable condition_;         // 用于等待和唤醒的条件变量
    bool stop_;                                 // 停止标志
};


int main(int args, char* argv[])
{
    
    return 0;
}