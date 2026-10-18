#include <future>
#include <chrono>
#include <iostream>
#include <thread>

int heavyWork() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 42;
}

class Calculator {
public:
    int heavyComputer(int x) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 42;
    }
};


int main(int argc, char const *argv[])
{
    std::future<int> fut = std::async(std::launch::async,heavyWork);
    std::cout << "doing other things " << std::endl;
    
    Calculator calc;
    
    std::future<int> classFut = std::async(
        std::launch::async,
        &Calculator::heavyComputer,
        &calc,
        10);

    int result = fut.get();
    int class_result = classFut.get();
    std::cout << "the works finished ! ";
    std::cin.get();
    return 0;
}



