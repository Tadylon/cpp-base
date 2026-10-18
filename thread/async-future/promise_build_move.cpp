#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <exception>

void background_work(std::promise<int> prom) {
    std::cout << "the work start ... " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    int result = 42;
    std::cout << "the work finished ! " << std::endl;
    prom.set_value(result);
}

void risky_task(std::promise<int> prom) {
    try {
        throw std::runtime_error("something go wrong ! ");
    } catch (...) {
        // 捕获异常，并通过 promise 传递给 future
        prom.set_exception(std::current_exception());
    }
}



int main () 
{
    // build this promise
    std::promise<int> this_1promise;
    std::promise<int> this_2promise;

    //put the promise to the future obj
    std::future<int> My_1future = this_1promise.get_future();
    std::future<int> My_2future = this_2promise.get_future();

    //3. start a new thread
    // 注意：promise 是不可拷贝的，必须使用 std::move 将其所有权转移给子线程
    std::thread worker_1thread(background_work,std::move(this_1promise));
    std::thread worker_2thread(risky_task,std::move(this_2promise));
    
    std::cout << "Main thread  running..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Main thread has finished" << std::endl;
    
    // 4. 获取结果。如果此时子线程还没调用 set_value，主线程会在这里卡住等待
    std::cout << "Main thread : waiting..." << std::endl;
    int final_1result = My_1future.get(); 
    try {
        int final_2result = My_2future.get(); 
    } catch (const std::exception& e) {
        std::cout << "catch error ! " << std::endl;
    }
    
    std::cout << "Main thread : return successful " << final_1result << std::endl;
    // std::cout << "Main thread : return successful " << final_2result << std::endl;
    
    // 5. 别忘了 join 线程
    worker_1thread.join();
    worker_2thread.join();
    return 0;

}




