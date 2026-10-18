#include <iostream>
using namespace std;
namespace MyNameSpace {
    int x = 10;

}
// using namespace MyNameSpace;


int main(){
    std::cout << MyNameSpace::x << std::endl;
    return 0;
}
