#include <iostream>
#include <coroutine>

// 1. 协程的返回类型（外部调用者持有的“遥控器”）
class SimpleGenerator {

public:
    // 2. 编译器要求必须名为 promise_type 的内嵌结构体（协程内部的“大管家”）
    struct promise_type {
        int current_value = 0; // 用于保存协程每次产出的数据

        // (A) 创建并返回外部的“遥控器”对象
        SimpleGenerator get_return_object() {
            return SimpleGenerator{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        // (B) 协程刚启动时：是否立即挂起？（suspend_always 表示先挂起，等外部唤醒才开始跑）
        std::suspend_always initial_suspend() noexcept { return {}; }

        // (C) 协程即将结束时：是否挂起？（必须挂起，以便外部安全检查结束状态并手动销毁资源）
        std::suspend_always final_suspend() noexcept { return {}; }

        // (D) 处理 co_yield 表达式：保存值，并挂起协程
        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }

        // (E) 处理没有返回值的 co_return（或函数自然执行到末尾）
        void return_void() noexcept {}

        // (F) 异常处理
        void unhandled_exception() { std::exit(1); }
    };
private:
    // 3. 协程句柄：底层指向堆上“协程帧”的指针，用来恢复或销毁协程
    std::coroutine_handle<promise_type> handle;
    // explicit SimpleGenerator(std::coroutine_handle<promise_type> p): handle(p) {}
    explicit SimpleGenerator(std::coroutine_handle<promise_type> h) : handle(h) {}
public:
    SimpleGenerator(const SimpleGenerator&) = delete;
    SimpleGenerator& operator=(const SimpleGenerator&) = delete;
    SimpleGenerator(SimpleGenerator&& n) noexcept: handle(std::exchange(n.handle, {})) {};

    // 析构时必须手动销毁协程帧，防止内存泄漏
    ~SimpleGenerator() {
        if (handle) handle.destroy();
    }

    // 供外部调用的接口：唤醒协程执行下一步
    bool next() {
        if (!handle || handle.done()) return false;
        handle.resume(); // 核心操作：从上次挂起的地方恢复执行！
        return !handle.done();
    }

    // 供外部调用的接口：获取当前产出的值
    int value() const {
        return handle.promise().current_value;
    }
private:
    int current_value;
};

// ================= 真正的协程函数 =================
// 因为包含了 co_yield 关键字，编译器会将此函数改造为协程状态机
SimpleGenerator count_to_three() {
    std::cout << "  [Inside the coroutine] Execution begins; preparing to output 1\n";
    co_yield 1; // 第一次挂起

    std::cout << "  [Inside the coroutine] Execution begins; preparing to output 2\n";
    co_yield 2; // 第二次挂起

    std::cout << "  [Inside the coroutine] Execution begins; preparing to output 3\n";
    co_yield 3; // 第三次挂起

    std::cout << "  [Inside the coroutine] Resumed again, preparing to finish\n";
    // 隐式执行 co_return;
    co_return;
}

int main() {
    std::cout << "[Main] 1. Call `count_to_three()` to create a coroutine\n";
    SimpleGenerator gen = count_to_three();

    std::cout << "[Main] 2. The coroutine has been created, but due to `initial_suspend`, the function body has not yet started executing.\n";

    while (gen.next()) {
        std::cout << "[Main] Receiving the value returned by the coroutine: " << gen.value() << "\n";
    }

    std::cout << "[Main] 3. The coroutine has finished executing; exit the programme\n";
    return 0;
}