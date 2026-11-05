#include <iostream>
#include <fstream>
#include <string>

// using namespace std;
void test01()
{
	std::ifstream ifs;
	ifs.open("a.txt", std::ios::in);

	if (!ifs.is_open())
	{
		std::cout << "Open error ! " << std::endl;
		return;
	}

	//第一种方式
	//char buf[1024] = { 0 };
	//while (ifs >> buf)
	//{
	//	cout << buf << endl;
	//}

	//第二种
	//char buf[1024] = { 0 };
	//while (ifs.getline(buf,sizeof(buf)))
	//{
	//	cout << buf << endl;
	//}

	//第三种
	//string buf;
	//while (getline(ifs, buf))
	//{
	//	cout << buf << endl;
	//}
    
	char c;
	while ((c = ifs.get()) != EOF)
	{
		std::cout << c;
	}
	ifs.close();
}

int main() {

	test01();
	system("pause");
	return 0;
}
