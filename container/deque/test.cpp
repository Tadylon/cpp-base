#include <iostream>
#include <deque>

void printDeque(const std::deque<int>& d) 
{
	for (std::deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
		std::cout << *it << " " << std::endl;

	}
	std::cout << std::endl;
}
//deque构造
void test01() {

	std::deque<int> d1; //无参构造函数
	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
	}
	printDeque(d1);
	std::deque<int> d2(d1.begin(),d1.end());
	printDeque(d2);

	std::deque<int>d3(10,100);
	printDeque(d3);

	std::deque<int>d4 = d3;
	printDeque(d4);
}

int main() {
	test01();
	system("pause");
	return 0;
}
