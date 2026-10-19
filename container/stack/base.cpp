#include <iostream>
#include <stack>

//栈容器常用接口
void test01()
{
	//创建栈容器 栈容器必须符合先进后出
	std::stack<int> s;

	//向栈中添加元素，叫做 压栈 入栈
	s.push(10);
	s.push(20);
	s.push(30);

	while (!s.empty()) {
		//输出栈顶元素
		std::cout << "top number is :  " << s.top() << std::endl;
		//弹出栈顶元素
		s.pop();
	}
	std::cout << "size of this stack is : " << s.size() << std::endl;

}

int main() {

	test01();

	system("pause");

	return 0;
}

