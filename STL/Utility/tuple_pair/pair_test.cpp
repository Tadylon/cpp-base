#include <iostream>
#include <tuple>
#include <string>
#include <utility>



void Get_Student(std::pair<std::string, int>& stu) {
    std::cout << "the name is : " << stu.first << "\n";
    std::cout << "the score is : " << stu.second << std::endl;
} 


int main()
{
    std::pair<std::string, int> wang = {"Li",98};
    Get_Student(wang);
    return 0;
}






