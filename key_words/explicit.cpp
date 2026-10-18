#include <iostream>
#include <memory>


class SmartPhone {
public:
    // 情况 A：没有使用 explicit
    // 编译器允许将 int 隐式转换为 SmartPhone 对象
    // SmartPhone(int price) : m_price(price) {}

    explicit SmartPhone() : m_price(0) {
        std::cout << "smartphone is built successfully, the price is : " << m_price << std::endl;
    }
    
    // 情况 B：使用了 explicit
    // 强制要求必须通过构造函数语法来创建对象
    explicit SmartPhone(int price) : m_price(price) {
        std::cout << "smartphone is built successfully, the price is : " << m_price << std::endl;
    }

    void displayPrice() const {
        std::cout << "the current price is : " << m_price << std::endl;
    }

private:
    int m_price;
};

void showPhoneInfo(const SmartPhone& phone) {
    phone.displayPrice();
}

int main() {
    // 1. 正确写法：显式调用构造函数
    SmartPhone p1(5999);
    
    // 2. 如果没有 explicit，下面这行是合法的（隐式转换）
    // 但有了 explicit，这行会编译报错：
    // Error: 无法从 "int" 转换为 "SmartPhone"
    SmartPhone p2(4999); 

    std::unique_ptr<SmartPhone> p3 = std::make_unique<SmartPhone>(323);


        // ✅ 正确：使用 reset
    auto p4 = std::make_unique<SmartPhone>();
    p4.reset(new SmartPhone(600));

    // 3. 函数调用中的隐式转换
    // 如果没有 explicit，我们可以直接传一个数字，编译器会自动帮我们“造”一个手机对象
    // 但这在逻辑上通常很奇怪：一个数字怎么能“变成”一个手机呢？
    showPhoneInfo(p2); // 报错：不存在从 "int" 到 "const SmartPhone" 的适当转换

    // 必须显式创建
    showPhoneInfo(SmartPhone(3999)); 

    return 0;
}