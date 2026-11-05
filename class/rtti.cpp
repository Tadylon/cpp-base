#include <iostream>
#include <typeinfo>

using namespace std;

class Flyable                       // 能飞的
{
public:
    virtual void takeoff() = 0;     // 起飞
    virtual void land() = 0;        // 降落

    // ~Flyable(){}
};


class Bird : public Flyable         // 鸟
{
public:
    void foraging() {}           // 觅食

    void takeoff() override {}

    void land() override {}

    virtual ~Bird(){}
};


class Plane : public Flyable        // 飞机
{
public:
    void carry() {}              // 运输
    void takeoff () override {}
    void land() override {}
};


void doSomething(Flyable *obj)                 // 做些事情
{
    obj->takeoff();

    cout << "class type now : " << typeid(*obj).name() << endl;        // 输出传入对象类型（"class Bird" or "class Plane"）

    if(typeid(*obj) == typeid(Bird))            // 判断对象类型
    {
        Bird *bird = dynamic_cast<Bird *>(obj); // 对象转化
        bird->foraging();
    }

    obj->land();
}

int main(){
	Bird *b = new Bird();
	doSomething(b);
	delete b;
	b = nullptr;
	return 0;
}