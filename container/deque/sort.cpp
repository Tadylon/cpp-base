#include <iostream>
#include <deque>
#include <algorithm>

void printDeque(const std::deque<int>& d) 
{
	for (std::deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
		std::cout << *it << " ";

	}
	std::cout << std::endl;
}

void test01()
{

	std::deque<int> d;
	d.push_back(10);
	d.push_back(20);
	d.push_front(100);
	d.push_front(200);
    for (int a =2; a < 10 ; a++) {
        d.push_back(a);
    }

	printDeque(d);
	sort(d.begin(), d.end());
	printDeque(d);

}

int main() {
	test01();
	system("pause");
	return 0;
}

