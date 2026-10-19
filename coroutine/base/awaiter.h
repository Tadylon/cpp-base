#include <coroutine>

// 永远挂起的 Awaiter
struct suspend_always {
    constexpr bool await_ready() const noexcept { return false; } // 1. 永远没准备好 -> 必须挂起！
    constexpr void await_suspend(std::coroutine_handle<>) const noexcept {} // 2. 挂起后什么额外操作都不做，直接返回调用者
    constexpr void await_resume() const noexcept {} // 3. 恢复后不返回任何值
};

// 永不挂起的 Awaiter
struct suspend_never {
    constexpr bool await_ready() const noexcept { return true; }  // 1. 永远准备好了 -> 直接跳过挂起，继续往下走！
    constexpr void await_suspend(std::coroutine_handle<>) const noexcept {}
    constexpr void await_resume() const noexcept {}
};