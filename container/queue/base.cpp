#include <iostream>
#include <queue>
#include <string>

class Person
{
public:
	Person(std::string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	std::string m_Name;
	int m_Age;
};

void test01() {

	//创建队列
	std::queue<Person> q;

	//准备数据
	Person p1("master", 30);
	Person p2("first sun", 1000);
	Person p3("PG one", 900);
	Person p4("fish", 800);

	//向队列中添加元素  入队操作
	q.push(p1);
	q.push(p2);
	q.push(p3);
	q.push(p4);

	//队列不提供迭代器，更不支持随机访问	
	while (!q.empty()) {
		//输出队头元素
		std::cout << "element in queue head -- name :  " << q.front().m_Name 
                  << " age :  "<< q.front().m_Age << std::endl;

		std::cout << "element in queue back -- name : " << q.back().m_Name  
                  << " age " << q.back().m_Age << std::endl;
        
		std::cout << std::endl;
		//弹出队头元素
		q.pop();
	}

	std::cout << "the size of queue: " << q.size() << std::endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}

