#include <iostream>
#include <vector>
#include <iterator>
// void printVector(std::vector<int>& v) {

// 	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
// 		std::cout << *it << " ";
// 	}
// 	std::cout << std::endl;
// }

void printVector(std::vector<int> & v){
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

}


void test01()
{
	std::vector<int>v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	printVector(v1);

	std::vector<int>v2;
	for (int i = 10; i > 0; i--)
	{
		v2.push_back(i);
	}
	printVector(v2);

	//互换容器
	std::cout << "After exchange : " << std::endl;
	v1.swap(v2);
	printVector(v1);
	printVector(v2);
}

void test02()
{
	std::vector<int> v;
	for (int i = 0; i < 100000; i++) {
		v.push_back(i);
	}

	std::cout << "The container of v is : " << v.capacity() << std::endl;
	std::cout << "The size of v is : " << v.size() << std::endl;

	v.resize(3);

	std::cout << "The container of v is : " << v.capacity() << std::endl;
	std::cout << "The size of v is : " << v.size() << std::endl;

	//收缩内存
	std::vector<int>(v).swap(v); //匿名对象

	std::cout << "The container of v is : " << v.capacity() << std::endl;
	std::cout << "The size of v is : " << v.size() << std::endl;
}

int main() {
	test01();
	test02();
	system("pause");
	return 0;
}

