#include <thread>
#include <future>
#include <iostream>
#include <vector>
#include <utility>

int heavy_task(int n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return n*n;
}


int main () {
    std::vector<std::thread> vthreads;
    std::vector<std::future<int>> futures;
    // std::vector<std::promise<int>> promises(100); // 注意 promise 不可拷贝，需用 move

    for (int i = 0; i < 100; ++i) {
        std::promise<int> prom;
        // promises[i] = std::promise<int>();

        futures.push_back(prom.get_future());
        vthreads.emplace_back([i, p = std::move(prom)]() mutable {
            int result = heavy_task(i);
            p.set_value(result); // 线程内设置值
        });
    }

    // 此时不需要先 join 再取值。我们可以直接从 future 中拿结果，
    // future.get() 自动具备阻塞等待对应线程结束的功能。
    std::cout << "--- collecting the result of async ! ---" << std::endl;
    for (auto &t : vthreads) {
        if (t.joinable()) {
            t.join();
        }
    }
    std::cout << "the async has finished ! " << std::endl;
    std::cin.get();
    return 0;
}




