#include <iostream>
#include <deque>

void printDeque(const std::deque<int>& d) 
{
	for (std::deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
		std::cout << *it << "   ";

	}
	std::cout << std::endl;
}

//大小操作
void test01()
{
	std::deque<int> d1;
	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
        d1.push_front(i);

        d1.push_back(i);
        d1.push_front(i);
	}
	printDeque(d1);

	//判断容器是否为空
	if (d1.empty()) {
		std::cout << "d1 is empty!" << std::endl;
	}
	else {
		std::cout << "d1 is not empty!" << std::endl;
		//统计大小
		std::cout << "d1 is large: " << d1.size() << std::endl;
	}

	//重新指定大小
	d1.resize(15, 1);
	printDeque(d1);

	d1.resize(5);
	printDeque(d1);
}

int main() {

	test01();

	system("pause");

	return 0;
}

