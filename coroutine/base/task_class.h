#include <coroutine>
#include <iostream>
#include <cstdint>

class Task
{
public:
    struct promise_type;
    using Handle = std::coroutine_handle<promise_type>;

    struct promise_type
    {
        Task get_return_object()
        {
            return Task{
                Handle::from_promise(*this)
            };
        }

        std::suspend_always initial_suspend() noexcept
        {
            return {};
        }

        std::suspend_always final_suspend() noexcept
        {
            return {};
        }

        void return_void() noexcept
        {
        }

        void unhandled_exception()
        {
            std::terminate();
        }
    };

    explicit Task(Handle h) noexcept
        : handle(h)
    {
    }
    //这里是对拷贝function，constructor，
    Task(const Task&) = delete;

    Task& operator=(const Task&) = delete;

    Task(Task&& other) noexcept
        : handle(std::exchange(other.handle, {}))
    {}

    Task& operator=(Task&& other) = delete;

    ~Task()
    {
        if (handle)
        {
            handle.destroy();
        }
    }

    bool resume()
    {
        if (!handle || handle.done())
        {
            return false;
        }
        handle.resume();
        return !handle.done();
    }

private:
    Handle handle;

};


Task example()
{
    std::cout << "Step 1\n";
    co_await std::suspend_always{};

    std::cout << "Step 2\n";
    co_await std::suspend_always{};

    std::cout << "Step 3\n";
    co_return;
}
