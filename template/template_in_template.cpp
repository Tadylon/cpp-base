#include <vector>
#include <string>
#include <iostream>

#include "print_obj.h"


template<typename T>
class MyContainer {
    std::vector<T> data;   // 直接指定模板参数 T
public:
    void add(const T& val) { data.push_back(val); }
};


template<typename T>
void printVectorSize(const std::vector<T>& vec) {
    std::cout << vec.size() << std::endl;
}


template <typename T, template <typename...> class Container>
class MyWrapper {
    Container<T> c;   // Container 是一个模板，这里用 T 实例化
public:
    void add(const T& val) { c.push_back(val); }
    // ...
    Container<T>& getContainer() {
        return c;
    }
    void PrintContainer() {
        for (auto i : this->c) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
};

int main()
{

    MyWrapper<int, std::vector> w;  // 底层使用 std::vector<int>
    w.add(42);
    w.getContainer().push_back(12);
    for (auto i : w.getContainer()) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    w.PrintContainer();
    std::cin.get();
    return 0;
}



