#include <iostream>
using namespace std;

#include <stack>

//栈容器常用接口
void test01()
{
	// //创建栈容器 栈容器必须符合先进后出
	// stack<int> s;

	// //向栈中添加元素，叫做 压栈 入栈
	// s.push(10);
	// s.push(20);
	// s.push(30);

	// while (!s.empty()) {
	// 	//输出栈顶元素
	// 	cout << "栈顶元素为： " << s.top() << endl;
	// 	//弹出栈顶元素
	// 	s.pop();
	// }
	// cout << "栈的大小为：" << s.size() << endl;
    stack<int> s;
    s.push(99);
    s.push(50);
    s.push(20);

    cout << "size of this stack : " << s.size() << endl;
    
    while (!s.empty()) {
        cout << "the top number is : " << s.top() << endl;

        //进行移除栈顶元素
        s.pop();
    }
    cout << "size of this stack : " << s.size() << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}

