#include <iostream>
#include <set>
#include <map>

#include "print_obj.h"


int main()
{
    std::set<int> test = {1,2,4,4564};
    std::cout << "the size of test set is : " << test.size() << std::endl;
    for (std::set<int>::iterator i = test.begin();i != test.end(); ++i) {
        std::cout << *i << " ";
    }
    
    std::cout << std::endl;
    for (auto i = test.begin();i != test.end(); ++i) {
        std::cout << *i << " ";
    }
    
    std::cout << std::endl;
    for (std::set<int>::const_iterator i = test.cbegin();i != test.cend(); ++i) {
        std::cout << *i << " ";
    }
    
    std::cout << std::endl;
    for (std::set<int>::iterator i = test.begin();i != test.end(); ++i) {
        std::cout << *i << " ";
    }

    return 0;
}











