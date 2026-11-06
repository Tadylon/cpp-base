#include <iostream>
#include <vector>
#include <fstream>


namespace MyNameSpace {
    int x = 10;
}
// using namespace MyNameSpace;

namespace pans{

namespace detail{


} // in namespace pans::detail

namespace {
    std::vector<int> list_vec{1,34,454,1321,342};
} // in without anonymous namespace

} // in namespace pans


void write_to_file()
{
    std::ofstream txt{"test.txt",std::ios::app};
    for (auto ctx : pans::list_vec) {
        txt << ctx << "\n";
    }
    txt << std::endl;
}


int main(){
    std::cout << MyNameSpace::x << std::endl;
    write_to_file();

    return 0;
}
