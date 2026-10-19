#include <iostream>
#include <vector>

void printVector(std::vector<int>& v) {

	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		std::cout<< *it << " ";
	}
	std::cout<< std::endl;
}

//插入和删除
void test01()
{
	std::vector<int> v1;
	//尾插
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);
	printVector(v1);
	//尾删
	v1.pop_back();
	printVector(v1);
	//插入
	v1.insert(v1.begin(), 100);
	printVector(v1);

	v1.insert(v1.begin(), 2, 1000);
	printVector(v1);
	std::cout<< v1.size() << std::endl;
	
	//删除
	v1.erase(v1.begin());
	printVector(v1);

	//清空
	v1.erase(v1.begin(), v1.end());
	v1.clear();
	printVector(v1);

}

int main() {

	test01();

	system("pause");

	return 0;
}

