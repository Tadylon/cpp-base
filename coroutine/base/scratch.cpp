#include <coroutine>
#include <iostream>
#include <exception>
#include <utility>

#include "task_class.h"
#include "awaiter.h"


int main()
{
    Task task = example();
    std::cout << "Main 1\n";

    task.resume();
    std::cout << "Main 2\n";

    task.resume();
    std::cout << "Main 3\n";

    task.resume();
    std::cout << "Main 4\n";
    
}