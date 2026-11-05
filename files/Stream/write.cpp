#include <iostream>
#include <fstream>
#include <iosfwd>
// using namespace std;

void test01()
{
	std::ofstream ofs;
	ofs.open("a.txt", std::ios::out | std::ios::app);
    // std::fstream test;
	ofs << "name   : zhangsan" << std::endl;
	ofs << "gender : man" << std::endl;
	ofs << "age    : 18" << std::endl;

	ofs.close();
}

int main() {

	test01();

	system("pause");

	return 0;
}


