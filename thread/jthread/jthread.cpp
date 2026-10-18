#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

// ❌ std::thread 的问题
void worker() {
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

void problem1() {
    std::thread t(worker);
    // 忘记调用 t.join() 或 t.detach()
    // 析构时调用 std::terminate()，程序崩溃！
}

void problem2() {
    std::thread t(worker);
    // 异常发生时，t 没有被 join
    throw std::runtime_error("oops");
    t.join();  // 永远不会执行
}

void simpleTask() {
    std::cout << "Thread " << std::this_thread::get_id() << " running" << std::endl;
}

// 方式3：函数对象
struct Task {
    void operator()() const {
        std::cout << "Function object" << std::endl;
    }
};

// 方式4：成员函数
class MyClass {
public:
    void memberFunc(int x) {
        std::cout << "Member function: " << x << std::endl;
    }
};

int main()
{
    // 方式1：函数指针
    std::jthread t1(simpleTask);
    
    // 方式2：lambda
    std::jthread t2([](int x) {
        std::cout << "Lambda with " << x << std::endl;
    }, 42);
    

    std::jthread t3(Task{});


    MyClass obj;
    std::jthread t4(&MyClass::memberFunc, &obj, 100);
    
    // 自动 join，无需手动调用
    return 0;
}









